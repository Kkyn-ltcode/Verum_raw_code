static void dissect_rtp_rfc2198 ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree ) {
 gint offset = 0 ;
 guint8 octet1 ;
 int cnt ;
 gboolean hdr_follow = TRUE ;
 proto_item * ti = NULL ;
 proto_tree * rfc2198_tree = NULL ;
 proto_tree * rfc2198_hdr_tree = NULL ;
 rfc2198_hdr * hdr_last , * hdr_new ;
 rfc2198_hdr * hdr_chain = NULL ;
 struct _rtp_conversation_info * p_conv_data = NULL ;
 gchar * payload_type_str ;
 p_conv_data = ( struct _rtp_conversation_info * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_rtp , 0 ) ;
 ti = proto_tree_add_text ( tree , tvb , offset , - 1 , "RFC 2198: Redundant Audio Data" ) ;
 rfc2198_tree = proto_item_add_subtree ( ti , ett_rtp_rfc2198 ) ;
 hdr_last = NULL ;
 cnt = 0 ;
 while ( hdr_follow ) {
 cnt ++ ;
 payload_type_str = NULL ;
 hdr_new = wmem_new ( wmem_packet_scope ( ) , rfc2198_hdr ) ;
 hdr_new -> next = NULL ;
 octet1 = tvb_get_guint8 ( tvb , offset ) ;
 hdr_new -> pt = RTP_PAYLOAD_TYPE ( octet1 ) ;
 hdr_follow = ( octet1 & 0x80 ) ;
 if ( ( hdr_new -> pt > 95 ) && ( hdr_new -> pt < 128 ) ) {
 if ( p_conv_data && p_conv_data -> rtp_dyn_payload ) {
 encoding_name_and_rate_t * encoding_name_and_rate_pt = NULL ;
 encoding_name_and_rate_pt = ( encoding_name_and_rate_t * ) g_hash_table_lookup ( p_conv_data -> rtp_dyn_payload , & hdr_new -> pt ) ;
 if ( encoding_name_and_rate_pt ) {
 payload_type_str = encoding_name_and_rate_pt -> encoding_name ;
 }
 }
 }
 ti = proto_tree_add_text ( rfc2198_tree , tvb , offset , ( hdr_follow ) ? 4 : 1 , "Header %u" , cnt ) ;
 rfc2198_hdr_tree = proto_item_add_subtree ( ti , ett_rtp_rfc2198_hdr ) ;
 proto_tree_add_item ( rfc2198_hdr_tree , hf_rtp_rfc2198_follow , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_uint_format_value ( rfc2198_hdr_tree , hf_rtp_payload_type , tvb , offset , 1 , octet1 , "%s (%u)" , payload_type_str ? payload_type_str : val_to_str_ext_const ( hdr_new -> pt , & rtp_payload_type_vals_ext , "Unknown" ) , hdr_new -> pt ) ;
 proto_item_append_text ( ti , ": PT=%s" , payload_type_str ? payload_type_str : val_to_str_ext ( hdr_new -> pt , & rtp_payload_type_vals_ext , "Unknown (%u)" ) ) ;
 offset += 1 ;
 if ( hdr_follow ) {
 proto_tree_add_item ( rfc2198_hdr_tree , hf_rtp_rfc2198_tm_off , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( rfc2198_hdr_tree , hf_rtp_rfc2198_bl_len , tvb , offset + 1 , 2 , ENC_BIG_ENDIAN ) ;
 hdr_new -> len = tvb_get_ntohs ( tvb , offset + 1 ) & 0x03FF ;
 proto_item_append_text ( ti , ", len=%u" , hdr_new -> len ) ;
 offset += 3 ;
 }
 else {
 hdr_new -> len = - 1 ;
 hdr_follow = FALSE ;
 }
 if ( hdr_last ) {
 hdr_last -> next = hdr_new ;
 }
 else {
 hdr_chain = hdr_new ;
 }
 hdr_last = hdr_new ;
 }
 hdr_last = hdr_chain ;
 while ( hdr_last ) {
 hdr_last -> offset = offset ;
 if ( ! hdr_last -> next ) {
 hdr_last -> len = tvb_reported_length_remaining ( tvb , offset ) ;
 }
 dissect_rtp_data ( tvb , pinfo , tree , rfc2198_tree , hdr_last -> offset , hdr_last -> len , hdr_last -> len , hdr_last -> pt ) ;
 offset += hdr_last -> len ;
 hdr_last = hdr_last -> next ;
 }
 }