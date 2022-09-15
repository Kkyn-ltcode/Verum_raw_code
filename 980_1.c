static gchar * logcat_log ( const struct dumper_t * dumper , guint32 seconds , gint microseconds , gint pid , gint tid , gchar priority , const gchar * tag , const gchar * log ) {
 gchar time_buffer [ 15 ] ;
 time_t datetime ;
 datetime = ( time_t ) seconds ;
 switch ( dumper -> type ) {
 case DUMP_BRIEF : return g_strdup_printf ( "%c/%-8s(%5i): %s\n" , priority , tag , pid , log ) ;
 case DUMP_PROCESS : return g_strdup_printf ( "%c(%5i) %s (%s)\n" , priority , pid , log , "" ) ;
 case DUMP_TAG : return g_strdup_printf ( "%c/%-8s: %s\n" , priority , tag , log ) ;
 case DUMP_THREAD : return g_strdup_printf ( "%c(%5i:0x%02x) %s\n" , priority , pid , tid , log ) ;
 case DUMP_TIME : strftime ( time_buffer , sizeof ( time_buffer ) , "%m-%d %H:%M:%S" , gmtime ( & datetime ) ) ;
 return g_strdup_printf ( "%s.%03i %c/%-8s(%5i): %s\n" , time_buffer , microseconds , priority , tag , pid , log ) ;
 case DUMP_THREADTIME : strftime ( time_buffer , sizeof ( time_buffer ) , "%m-%d %H:%M:%S" , gmtime ( & datetime ) ) ;
 return g_strdup_printf ( "%s.%03i %5i %5i %c %-8s: %s\n" , time_buffer , microseconds , pid , tid , priority , tag , log ) ;
 case DUMP_LONG : strftime ( time_buffer , sizeof ( time_buffer ) , "%m-%d %H:%M:%S" , gmtime ( & datetime ) ) ;
 return g_strdup_printf ( "[ %s.%03i %5i:0x%02x %c/%s ]\n%s\n\n" , time_buffer , microseconds , pid , tid , priority , tag , log ) ;
 default : return NULL ;
 }
 }