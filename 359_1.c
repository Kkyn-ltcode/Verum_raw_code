static void vc1_mc_1mv ( VC1Context * v , int dir ) {
 MpegEncContext * s = & v -> s ;
 DSPContext * dsp = & v -> s . dsp ;
 H264ChromaContext * h264chroma = & v -> h264chroma ;
 uint8_t * srcY , * srcU , * srcV ;
 int dxy , mx , my , uvmx , uvmy , src_x , src_y , uvsrc_x , uvsrc_y ;
 int off , off_uv ;
 int v_edge_pos = s -> v_edge_pos >> v -> field_mode ;
 if ( ( ! v -> field_mode || ( v -> ref_field_type [ dir ] == 1 && v -> cur_field_type == 1 ) ) && ! v -> s . last_picture . f . data [ 0 ] ) return ;
 mx = s -> mv [ dir ] [ 0 ] [ 0 ] ;
 my = s -> mv [ dir ] [ 0 ] [ 1 ] ;
 if ( s -> pict_type == AV_PICTURE_TYPE_P ) {
 s -> current_picture . f . motion_val [ 1 ] [ s -> block_index [ 0 ] + v -> blocks_off ] [ 0 ] = mx ;
 s -> current_picture . f . motion_val [ 1 ] [ s -> block_index [ 0 ] + v -> blocks_off ] [ 1 ] = my ;
 }
 uvmx = ( mx + ( ( mx & 3 ) == 3 ) ) >> 1 ;
 uvmy = ( my + ( ( my & 3 ) == 3 ) ) >> 1 ;
 v -> luma_mv [ s -> mb_x ] [ 0 ] = uvmx ;
 v -> luma_mv [ s -> mb_x ] [ 1 ] = uvmy ;
 if ( v -> field_mode && v -> cur_field_type != v -> ref_field_type [ dir ] ) {
 my = my - 2 + 4 * v -> cur_field_type ;
 uvmy = uvmy - 2 + 4 * v -> cur_field_type ;
 }
 if ( v -> fastuvmc && ( v -> fcm != ILACE_FRAME ) ) {
 uvmx = uvmx + ( ( uvmx < 0 ) ? ( uvmx & 1 ) : - ( uvmx & 1 ) ) ;
 uvmy = uvmy + ( ( uvmy < 0 ) ? ( uvmy & 1 ) : - ( uvmy & 1 ) ) ;
 }
 if ( v -> field_mode ) {
 if ( ! dir ) {
 if ( ( v -> cur_field_type != v -> ref_field_type [ dir ] ) && v -> cur_field_type ) {
 srcY = s -> current_picture . f . data [ 0 ] ;
 srcU = s -> current_picture . f . data [ 1 ] ;
 srcV = s -> current_picture . f . data [ 2 ] ;
 }
 else {
 srcY = s -> last_picture . f . data [ 0 ] ;
 srcU = s -> last_picture . f . data [ 1 ] ;
 srcV = s -> last_picture . f . data [ 2 ] ;
 }
 }
 else {
 srcY = s -> next_picture . f . data [ 0 ] ;
 srcU = s -> next_picture . f . data [ 1 ] ;
 srcV = s -> next_picture . f . data [ 2 ] ;
 }
 }
 else {
 if ( ! dir ) {
 srcY = s -> last_picture . f . data [ 0 ] ;
 srcU = s -> last_picture . f . data [ 1 ] ;
 srcV = s -> last_picture . f . data [ 2 ] ;
 }
 else {
 srcY = s -> next_picture . f . data [ 0 ] ;
 srcU = s -> next_picture . f . data [ 1 ] ;
 srcV = s -> next_picture . f . data [ 2 ] ;
 }
 }
 src_x = s -> mb_x * 16 + ( mx >> 2 ) ;
 src_y = s -> mb_y * 16 + ( my >> 2 ) ;
 uvsrc_x = s -> mb_x * 8 + ( uvmx >> 2 ) ;
 uvsrc_y = s -> mb_y * 8 + ( uvmy >> 2 ) ;
 if ( v -> profile != PROFILE_ADVANCED ) {
 src_x = av_clip ( src_x , - 16 , s -> mb_width * 16 ) ;
 src_y = av_clip ( src_y , - 16 , s -> mb_height * 16 ) ;
 uvsrc_x = av_clip ( uvsrc_x , - 8 , s -> mb_width * 8 ) ;
 uvsrc_y = av_clip ( uvsrc_y , - 8 , s -> mb_height * 8 ) ;
 }
 else {
 src_x = av_clip ( src_x , - 17 , s -> avctx -> coded_width ) ;
 src_y = av_clip ( src_y , - 18 , s -> avctx -> coded_height + 1 ) ;
 uvsrc_x = av_clip ( uvsrc_x , - 8 , s -> avctx -> coded_width >> 1 ) ;
 uvsrc_y = av_clip ( uvsrc_y , - 8 , s -> avctx -> coded_height >> 1 ) ;
 }
 srcY += src_y * s -> linesize + src_x ;
 srcU += uvsrc_y * s -> uvlinesize + uvsrc_x ;
 srcV += uvsrc_y * s -> uvlinesize + uvsrc_x ;
 if ( v -> field_mode && v -> ref_field_type [ dir ] ) {
 srcY += s -> current_picture_ptr -> f . linesize [ 0 ] ;
 srcU += s -> current_picture_ptr -> f . linesize [ 1 ] ;
 srcV += s -> current_picture_ptr -> f . linesize [ 2 ] ;
 }
 if ( s -> flags & CODEC_FLAG_GRAY ) {
 srcU = s -> edge_emu_buffer + 18 * s -> linesize ;
 srcV = s -> edge_emu_buffer + 18 * s -> linesize ;
 }
 if ( v -> rangeredfrm || ( v -> mv_mode == MV_PMODE_INTENSITY_COMP ) || s -> h_edge_pos < 22 || v_edge_pos < 22 || ( unsigned ) ( src_x - s -> mspel ) > s -> h_edge_pos - ( mx & 3 ) - 16 - s -> mspel * 3 || ( unsigned ) ( src_y - 1 ) > v_edge_pos - ( my & 3 ) - 16 - 3 ) {
 uint8_t * uvbuf = s -> edge_emu_buffer + 19 * s -> linesize ;
 srcY -= s -> mspel * ( 1 + s -> linesize ) ;
 s -> vdsp . emulated_edge_mc ( s -> edge_emu_buffer , srcY , s -> linesize , 17 + s -> mspel * 2 , 17 + s -> mspel * 2 , src_x - s -> mspel , src_y - s -> mspel , s -> h_edge_pos , v_edge_pos ) ;
 srcY = s -> edge_emu_buffer ;
 s -> vdsp . emulated_edge_mc ( uvbuf , srcU , s -> uvlinesize , 8 + 1 , 8 + 1 , uvsrc_x , uvsrc_y , s -> h_edge_pos >> 1 , v_edge_pos >> 1 ) ;
 s -> vdsp . emulated_edge_mc ( uvbuf + 16 , srcV , s -> uvlinesize , 8 + 1 , 8 + 1 , uvsrc_x , uvsrc_y , s -> h_edge_pos >> 1 , v_edge_pos >> 1 ) ;
 srcU = uvbuf ;
 srcV = uvbuf + 16 ;
 if ( v -> rangeredfrm ) {
 int i , j ;
 uint8_t * src , * src2 ;
 src = srcY ;
 for ( j = 0 ;
 j < 17 + s -> mspel * 2 ;
 j ++ ) {
 for ( i = 0 ;
 i < 17 + s -> mspel * 2 ;
 i ++ ) src [ i ] = ( ( src [ i ] - 128 ) >> 1 ) + 128 ;
 src += s -> linesize ;
 }
 src = srcU ;
 src2 = srcV ;
 for ( j = 0 ;
 j < 9 ;
 j ++ ) {
 for ( i = 0 ;
 i < 9 ;
 i ++ ) {
 src [ i ] = ( ( src [ i ] - 128 ) >> 1 ) + 128 ;
 src2 [ i ] = ( ( src2 [ i ] - 128 ) >> 1 ) + 128 ;
 }
 src += s -> uvlinesize ;
 src2 += s -> uvlinesize ;
 }
 }
 if ( v -> mv_mode == MV_PMODE_INTENSITY_COMP ) {
 int i , j ;
 uint8_t * src , * src2 ;
 src = srcY ;
 for ( j = 0 ;
 j < 17 + s -> mspel * 2 ;
 j ++ ) {
 for ( i = 0 ;
 i < 17 + s -> mspel * 2 ;
 i ++ ) src [ i ] = v -> luty [ src [ i ] ] ;
 src += s -> linesize ;
 }
 src = srcU ;
 src2 = srcV ;
 for ( j = 0 ;
 j < 9 ;
 j ++ ) {
 for ( i = 0 ;
 i < 9 ;
 i ++ ) {
 src [ i ] = v -> lutuv [ src [ i ] ] ;
 src2 [ i ] = v -> lutuv [ src2 [ i ] ] ;
 }
 src += s -> uvlinesize ;
 src2 += s -> uvlinesize ;
 }
 }
 srcY += s -> mspel * ( 1 + s -> linesize ) ;
 }
 if ( v -> field_mode && v -> cur_field_type ) {
 off = s -> current_picture_ptr -> f . linesize [ 0 ] ;
 off_uv = s -> current_picture_ptr -> f . linesize [ 1 ] ;
 }
 else {
 off = 0 ;
 off_uv = 0 ;
 }
 if ( s -> mspel ) {
 dxy = ( ( my & 3 ) << 2 ) | ( mx & 3 ) ;
 v -> vc1dsp . put_vc1_mspel_pixels_tab [ dxy ] ( s -> dest [ 0 ] + off , srcY , s -> linesize , v -> rnd ) ;
 v -> vc1dsp . put_vc1_mspel_pixels_tab [ dxy ] ( s -> dest [ 0 ] + off + 8 , srcY + 8 , s -> linesize , v -> rnd ) ;
 srcY += s -> linesize * 8 ;
 v -> vc1dsp . put_vc1_mspel_pixels_tab [ dxy ] ( s -> dest [ 0 ] + off + 8 * s -> linesize , srcY , s -> linesize , v -> rnd ) ;
 v -> vc1dsp . put_vc1_mspel_pixels_tab [ dxy ] ( s -> dest [ 0 ] + off + 8 * s -> linesize + 8 , srcY + 8 , s -> linesize , v -> rnd ) ;
 }
 else {
 dxy = ( my & 2 ) | ( ( mx & 2 ) >> 1 ) ;
 if ( ! v -> rnd ) dsp -> put_pixels_tab [ 0 ] [ dxy ] ( s -> dest [ 0 ] + off , srcY , s -> linesize , 16 ) ;
 else dsp -> put_no_rnd_pixels_tab [ 0 ] [ dxy ] ( s -> dest [ 0 ] + off , srcY , s -> linesize , 16 ) ;
 }
 if ( s -> flags & CODEC_FLAG_GRAY ) return ;
 uvmx = ( uvmx & 3 ) << 1 ;
 uvmy = ( uvmy & 3 ) << 1 ;
 if ( ! v -> rnd ) {
 h264chroma -> put_h264_chroma_pixels_tab [ 0 ] ( s -> dest [ 1 ] + off_uv , srcU , s -> uvlinesize , 8 , uvmx , uvmy ) ;
 h264chroma -> put_h264_chroma_pixels_tab [ 0 ] ( s -> dest [ 2 ] + off_uv , srcV , s -> uvlinesize , 8 , uvmx , uvmy ) ;
 }
 else {
 v -> vc1dsp . put_no_rnd_vc1_chroma_pixels_tab [ 0 ] ( s -> dest [ 1 ] + off_uv , srcU , s -> uvlinesize , 8 , uvmx , uvmy ) ;
 v -> vc1dsp . put_no_rnd_vc1_chroma_pixels_tab [ 0 ] ( s -> dest [ 2 ] + off_uv , srcV , s -> uvlinesize , 8 , uvmx , uvmy ) ;
 }
 }