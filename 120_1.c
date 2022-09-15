static int dtls1_retrieve_buffered_fragment ( SSL * s , int * ok ) {
 pitem * item ;
 hm_fragment * frag ;
 int al ;
 * ok = 0 ;
 item = pqueue_peek ( s -> d1 -> buffered_messages ) ;
 if ( item == NULL ) return 0 ;
 frag = ( hm_fragment * ) item -> data ;
 if ( frag -> reassembly != NULL ) return 0 ;
 if ( s -> d1 -> handshake_read_seq == frag -> msg_header . seq ) {
 unsigned long frag_len = frag -> msg_header . frag_len ;
 pqueue_pop ( s -> d1 -> buffered_messages ) ;
 al = dtls1_preprocess_fragment ( s , & frag -> msg_header ) ;
 if ( al == 0 ) {
 unsigned char * p = ( unsigned char * ) s -> init_buf -> data + DTLS1_HM_HEADER_LENGTH ;
 memcpy ( & p [ frag -> msg_header . frag_off ] , frag -> fragment , frag -> msg_header . frag_len ) ;
 }
 dtls1_hm_fragment_free ( frag ) ;
 pitem_free ( item ) ;
 if ( al == 0 ) {
 * ok = 1 ;
 return frag_len ;
 }
 ssl3_send_alert ( s , SSL3_AL_FATAL , al ) ;
 s -> init_num = 0 ;
 * ok = 0 ;
 return - 1 ;
 }
 else return 0 ;
 }