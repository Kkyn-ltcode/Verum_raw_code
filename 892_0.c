static void isoent_free_all ( struct isoent * isoent ) {
 struct isoent * np , * np_temp ;
 if ( isoent == NULL ) return ;
 np = isoent ;
 for ( ;
 ;
 ) {
 if ( np -> dir ) {
 if ( np -> children . first != NULL ) {
 np = np -> children . first ;
 continue ;
 }
 }
 for ( ;
 ;
 ) {
 np_temp = np ;
 if ( np -> chnext == NULL ) {
 np = np -> parent ;
 _isoent_free ( np_temp ) ;
 if ( np == np_temp ) return ;
 }
 else {
 np = np -> chnext ;
 _isoent_free ( np_temp ) ;
 break ;
 }
 }
 }
 }