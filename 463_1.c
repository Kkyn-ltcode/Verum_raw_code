static void pic_as_field ( Picture * pic , const int parity ) {
 int i ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 if ( parity == PICT_BOTTOM_FIELD ) pic -> f . data [ i ] += pic -> f . linesize [ i ] ;
 pic -> f . reference = parity ;
 pic -> f . linesize [ i ] *= 2 ;
 }
 pic -> poc = pic -> field_poc [ parity == PICT_BOTTOM_FIELD ] ;
 }