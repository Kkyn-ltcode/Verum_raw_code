static inline struct extr_rec * extra_last_record ( struct isoent * isoent ) {
 if ( isoent -> extr_rec_list . first == NULL ) return ( NULL ) ;
 return ( ( struct extr_rec * ) ( void * ) ( ( char * ) ( isoent -> extr_rec_list . last ) - offsetof ( struct extr_rec , next ) ) ) ;
 }