static guint32 dissect_fullpacket ( tvbuff_t * tvb , guint32 offset , guint16 scallno , packet_info * pinfo , proto_tree * iax2_tree , proto_tree * main_tree ) {
 guint16 dcallno ;
 guint32 ts ;
 guint8 type ;
 guint8 csub ;
 guint32 codec ;
 proto_tree * packet_type_tree = NULL ;
 iax_call_data * iax_call ;
 iax_packet_data * iax_packet ;
 gboolean reversed ;
 gboolean rtp_marker ;
 dcallno = tvb_get_ntohs ( tvb , offset ) & 0x7FFF ;
 ts = tvb_get_ntohl ( tvb , offset + 2 ) ;
 type = tvb_get_guint8 ( tvb , offset + 8 ) ;
 csub = tvb_get_guint8 ( tvb , offset + 9 ) ;
 iax2_info -> ftype = type ;
 iax2_info -> csub = csub ;
 iax2_info -> scallno = scallno ;
 iax2_info -> dcallno = dcallno ;
 iax_packet = ( iax_packet_data * ) p_get_proto_data ( wmem_file_scope ( ) , pinfo , proto_iax2 , 0 ) ;
 if ( ! iax_packet ) {
 if ( type == AST_FRAME_IAX && csub == IAX_COMMAND_NEW ) {
 iax_call = iax_new_call ( pinfo , scallno ) ;
 reversed = FALSE ;
 }
 else {
 iax_call = iax_lookup_call ( pinfo , scallno , dcallno , & reversed ) ;
 }
 iax_packet = iax_new_packet_data ( iax_call , reversed ) ;
 p_add_proto_data ( wmem_file_scope ( ) , pinfo , proto_iax2 , 0 , iax_packet ) ;
 }
 else {
 iax_call = iax_packet -> call_data ;
 reversed = iax_packet -> reversed ;
 }
 iax2_populate_pinfo_from_packet_data ( pinfo , iax_packet ) ;
 if ( iax2_tree ) {
 proto_item * packet_type_base ;
 proto_tree_add_item ( iax2_tree , hf_iax2_dcallno , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( iax2_tree , hf_iax2_retransmission , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( iax_call ) {
 proto_item * item = proto_tree_add_uint ( iax2_tree , hf_iax2_callno , tvb , 0 , 4 , iax_call -> forward_circuit_ids [ 0 ] ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 }
 proto_tree_add_uint ( iax2_tree , hf_iax2_ts , tvb , offset + 2 , 4 , ts ) ;
 iax2_add_ts_fields ( pinfo , iax2_tree , iax_packet , ( guint16 ) ts ) ;
 proto_tree_add_item ( iax2_tree , hf_iax2_oseqno , tvb , offset + 6 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( iax2_tree , hf_iax2_iseqno , tvb , offset + 7 , 1 , ENC_BIG_ENDIAN ) ;
 packet_type_base = proto_tree_add_uint ( iax2_tree , hf_iax2_type , tvb , offset + 8 , 1 , type ) ;
 packet_type_tree = proto_item_add_subtree ( packet_type_base , ett_iax2_type ) ;
 }
 else {
 iax2_add_ts_fields ( pinfo , iax2_tree , iax_packet , ( guint16 ) ts ) ;
 }
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s, source call# %d, timestamp %ums" , val_to_str_ext ( type , & iax_frame_types_ext , "Unknown (0x%02x)" ) , scallno , ts ) ;
 iax2_info -> messageName = val_to_str_ext ( type , & iax_frame_types_ext , "Unknown (0x%02x)" ) ;
 switch ( type ) {
 case AST_FRAME_IAX : offset = dissect_iax2_command ( tvb , offset + 9 , pinfo , packet_type_tree , iax_packet ) ;
 iax2_info -> messageName = val_to_str_ext ( csub , & iax_iax_subclasses_ext , "unknown (0x%02x)" ) ;
 if ( csub < NUM_TAP_IAX_VOIP_STATES ) iax2_info -> callState = tap_iax_voip_state [ csub ] ;
 break ;
 case AST_FRAME_DTMF_BEGIN : case AST_FRAME_DTMF_END : proto_tree_add_item ( packet_type_tree , hf_iax2_dtmf_csub , tvb , offset + 9 , 1 , ENC_ASCII | ENC_NA ) ;
 offset += 10 ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " digit %c" , csub ) ;
 break ;
 case AST_FRAME_CONTROL : proto_tree_add_uint ( packet_type_tree , hf_iax2_cmd_csub , tvb , offset + 9 , 1 , csub ) ;
 offset += 10 ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " %s" , val_to_str_ext ( csub , & iax_cmd_subclasses_ext , "unknown (0x%02x)" ) ) ;
 iax2_info -> messageName = val_to_str_ext ( csub , & iax_cmd_subclasses_ext , "unknown (0x%02x)" ) ;
 if ( csub < NUM_TAP_CMD_VOIP_STATES ) iax2_info -> callState = tap_cmd_voip_state [ csub ] ;
 break ;
 case AST_FRAME_VOICE : iax_packet -> codec = codec = uncompress_subclass ( csub ) ;
 if ( packet_type_tree ) {
 proto_item * item ;
 proto_tree_add_item ( packet_type_tree , hf_iax2_voice_csub , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 item = proto_tree_add_uint ( packet_type_tree , hf_iax2_voice_codec , tvb , offset + 9 , 1 , codec ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 }
 offset += 10 ;
 if ( iax_call ) {
 if ( reversed ) {
 iax_call -> dst_codec = codec ;
 }
 else {
 iax_call -> src_codec = codec ;
 }
 }
 dissect_payload ( tvb , offset , pinfo , iax2_tree , main_tree , ts , FALSE , iax_packet ) ;
 break ;
 case AST_FRAME_VIDEO : rtp_marker = csub & 0x40 ? TRUE : FALSE ;
 iax_packet -> codec = codec = uncompress_subclass ( ( guint8 ) ( csub & ~ 40 ) ) ;
 if ( packet_type_tree ) {
 proto_item * item ;
 proto_tree_add_item ( packet_type_tree , hf_iax2_video_csub , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( packet_type_tree , hf_iax2_marker , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 item = proto_tree_add_uint ( packet_type_tree , hf_iax2_video_codec , tvb , offset + 9 , 1 , codec ) ;
 PROTO_ITEM_SET_GENERATED ( item ) ;
 }
 offset += 10 ;
 if ( iax_call && iax_packet -> first_time ) {
 if ( reversed ) {
 iax_call -> dst_vformat = codec ;
 }
 else {
 iax_call -> src_vformat = codec ;
 }
 }
 if ( rtp_marker ) col_append_str ( pinfo -> cinfo , COL_INFO , ", Mark" ) ;
 dissect_payload ( tvb , offset , pinfo , iax2_tree , main_tree , ts , TRUE , iax_packet ) ;
 break ;
 case AST_FRAME_MODEM : proto_tree_add_item ( packet_type_tree , hf_iax2_modem_csub , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 offset += 10 ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " %s" , val_to_str ( csub , iax_modem_subclasses , "unknown (0x%02x)" ) ) ;
 break ;
 case AST_FRAME_TEXT : proto_tree_add_item ( packet_type_tree , hf_iax2_text_csub , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 offset += 10 ;
 {
 int textlen = tvb_captured_length_remaining ( tvb , offset ) ;
 if ( textlen > 0 ) {
 proto_tree_add_item ( packet_type_tree , hf_iax2_text_text , tvb , offset , textlen , ENC_UTF_8 | ENC_NA ) ;
 offset += textlen ;
 }
 }
 break ;
 case AST_FRAME_HTML : proto_tree_add_item ( packet_type_tree , hf_iax2_html_csub , tvb , offset + 9 , 1 , ENC_BIG_ENDIAN ) ;
 offset += 10 ;
 if ( csub == 0x01 ) {
 int urllen = tvb_captured_length_remaining ( tvb , offset ) ;
 if ( urllen > 0 ) {
 proto_item * pi = proto_tree_add_item ( packet_type_tree , hf_iax2_html_url , tvb , offset , urllen , ENC_UTF_8 | ENC_NA ) ;
 PROTO_ITEM_SET_URL ( pi ) ;
 offset += urllen ;
 }
 }
 break ;
 case AST_FRAME_CNG : default : proto_tree_add_uint ( packet_type_tree , hf_iax2_csub , tvb , offset + 9 , 1 , csub ) ;
 offset += 10 ;
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " subclass %d" , csub ) ;
 break ;
 }
 iax_packet -> first_time = FALSE ;
 return offset ;
 }