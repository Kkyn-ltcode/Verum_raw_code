static int h261_decode_frame ( AVCodecContext * avctx , void * data , int * got_frame , AVPacket * avpkt ) {
 const uint8_t * buf = avpkt -> data ;
 int buf_size = avpkt -> size ;
 H261Context * h = avctx -> priv_data ;
 MpegEncContext * s = & h -> s ;
 int ret ;
 AVFrame * pict = data ;
 av_dlog ( avctx , "*****frame %d size=%d\n" , avctx -> frame_number , buf_size ) ;
 av_dlog ( avctx , "bytes=%x %x %x %x\n" , buf [ 0 ] , buf [ 1 ] , buf [ 2 ] , buf [ 3 ] ) ;
 s -> flags = avctx -> flags ;
 s -> flags2 = avctx -> flags2 ;
 h -> gob_start_code_skipped = 0 ;
 retry : init_get_bits ( & s -> gb , buf , buf_size * 8 ) ;
 if ( ! s -> context_initialized ) {
 if ( ff_MPV_common_init ( s ) < 0 ) return - 1 ;
 }
 if ( s -> current_picture_ptr == NULL || s -> current_picture_ptr -> f . data [ 0 ] ) {
 int i = ff_find_unused_picture ( s , 0 ) ;
 if ( i < 0 ) return i ;
 s -> current_picture_ptr = & s -> picture [ i ] ;
 }
 ret = h261_decode_picture_header ( h ) ;
 if ( ret < 0 ) {
 av_log ( s -> avctx , AV_LOG_ERROR , "header damaged\n" ) ;
 return - 1 ;
 }
 if ( s -> width != avctx -> coded_width || s -> height != avctx -> coded_height ) {
 ParseContext pc = s -> parse_context ;
 s -> parse_context . buffer = 0 ;
 ff_MPV_common_end ( s ) ;
 s -> parse_context = pc ;
 }
 if ( ! s -> context_initialized ) {
 avcodec_set_dimensions ( avctx , s -> width , s -> height ) ;
 goto retry ;
 }
 s -> current_picture . f . pict_type = s -> pict_type ;
 s -> current_picture . f . key_frame = s -> pict_type == AV_PICTURE_TYPE_I ;
 if ( ( avctx -> skip_frame >= AVDISCARD_NONREF && s -> pict_type == AV_PICTURE_TYPE_B ) || ( avctx -> skip_frame >= AVDISCARD_NONKEY && s -> pict_type != AV_PICTURE_TYPE_I ) || avctx -> skip_frame >= AVDISCARD_ALL ) return get_consumed_bytes ( s , buf_size ) ;
 if ( ff_MPV_frame_start ( s , avctx ) < 0 ) return - 1 ;
 ff_mpeg_er_frame_start ( s ) ;
 s -> mb_x = 0 ;
 s -> mb_y = 0 ;
 while ( h -> gob_number < ( s -> mb_height == 18 ? 12 : 5 ) ) {
 if ( ff_h261_resync ( h ) < 0 ) break ;
 h261_decode_gob ( h ) ;
 }
 ff_MPV_frame_end ( s ) ;
 assert ( s -> current_picture . f . pict_type == s -> current_picture_ptr -> f . pict_type ) ;
 assert ( s -> current_picture . f . pict_type == s -> pict_type ) ;
 * pict = s -> current_picture_ptr -> f ;
 ff_print_debug_info ( s , pict ) ;
 * got_frame = 1 ;
 return get_consumed_bytes ( s , buf_size ) ;
 }