static void h245_setup_channels ( packet_info * pinfo , channel_info_t * upcoming_channel_lcl ) {
 gint * key ;
 GHashTable * rtp_dyn_payload = NULL ;
 struct srtp_info * dummy_srtp_info = NULL ;
 if ( ! upcoming_channel_lcl ) return ;
 if ( ! strcmp ( upcoming_channel_lcl -> data_type_str , "t38fax" ) ) {
 if ( upcoming_channel_lcl -> media_addr . addr . type != AT_NONE && upcoming_channel_lcl -> media_addr . port != 0 ) {
 t38_add_address ( pinfo , & upcoming_channel_lcl -> media_addr . addr , upcoming_channel_lcl -> media_addr . port , 0 , "H245" , pinfo -> fd -> num ) ;
 }
 return ;
 }
 if ( upcoming_channel_lcl -> rfc2198 > 0 ) {
 encoding_name_and_rate_t * encoding_name_and_rate = wmem_new ( wmem_file_scope ( ) , encoding_name_and_rate_t ) ;
 rtp_dyn_payload = g_hash_table_new ( g_int_hash , g_int_equal ) ;
 encoding_name_and_rate -> encoding_name = wmem_strdup ( wmem_file_scope ( ) , "red" ) ;
 encoding_name_and_rate -> sample_rate = 8000 ;
 key = wmem_new ( wmem_file_scope ( ) , gint ) ;
 * key = upcoming_channel_lcl -> rfc2198 ;
 g_hash_table_insert ( rtp_dyn_payload , key , encoding_name_and_rate ) ;
 }
 if ( upcoming_channel_lcl -> srtp_flag ) {
 dummy_srtp_info = wmem_new0 ( wmem_file_scope ( ) , struct srtp_info ) ;
 }
 if ( upcoming_channel_lcl -> media_addr . addr . type != AT_NONE && upcoming_channel_lcl -> media_addr . port != 0 ) {
 srtp_add_address ( pinfo , & upcoming_channel_lcl -> media_addr . addr , upcoming_channel_lcl -> media_addr . port , 0 , "H245" , pinfo -> fd -> num , upcoming_channel_lcl -> is_video , rtp_dyn_payload , dummy_srtp_info ) ;
 }
 if ( upcoming_channel_lcl -> media_control_addr . addr . type != AT_NONE && upcoming_channel_lcl -> media_control_addr . port != 0 && rtcp_handle ) {
 srtcp_add_address ( pinfo , & upcoming_channel_lcl -> media_control_addr . addr , upcoming_channel_lcl -> media_control_addr . port , 0 , "H245" , pinfo -> fd -> num , dummy_srtp_info ) ;
 }
 }