static int decode_frame ( AVCodecContext * avctx , void * data , int * got_frame , AVPacket * avpkt ) {
 uint8_t ctable [ 128 ] ;
 QpegContext * const a = avctx -> priv_data ;
 AVFrame * const p = & a -> pic ;
 uint8_t * outdata ;
 int delta , ret ;
 const uint8_t * pal = av_packet_get_side_data ( avpkt , AV_PKT_DATA_PALETTE , NULL ) ;
 if ( avpkt -> size < 0x86 ) {
 av_log ( avctx , AV_LOG_ERROR , "Packet is too small\n" ) ;
 return AVERROR_INVALIDDATA ;
 }
 bytestream2_init ( & a -> buffer , avpkt -> data , avpkt -> size ) ;
 p -> reference = 3 ;
 if ( ( ret = avctx -> reget_buffer ( avctx , p ) ) < 0 ) {
 av_log ( avctx , AV_LOG_ERROR , "reget_buffer() failed\n" ) ;
 return ret ;
 }
 outdata = a -> pic . data [ 0 ] ;
 bytestream2_skip ( & a -> buffer , 4 ) ;
 bytestream2_get_buffer ( & a -> buffer , ctable , 128 ) ;
 bytestream2_skip ( & a -> buffer , 1 ) ;
 delta = bytestream2_get_byte ( & a -> buffer ) ;
 if ( delta == 0x10 ) {
 qpeg_decode_intra ( a , outdata , a -> pic . linesize [ 0 ] , avctx -> width , avctx -> height ) ;
 }
 else {
 qpeg_decode_inter ( a , outdata , a -> pic . linesize [ 0 ] , avctx -> width , avctx -> height , delta , ctable , a -> refdata ) ;
 }
 if ( pal ) {
 a -> pic . palette_has_changed = 1 ;
 memcpy ( a -> pal , pal , AVPALETTE_SIZE ) ;
 }
 memcpy ( a -> pic . data [ 1 ] , a -> pal , AVPALETTE_SIZE ) ;
 * got_frame = 1 ;
 * ( AVFrame * ) data = a -> pic ;
 return avpkt -> size ;
 }