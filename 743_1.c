static int parse_RowsBuffer ( tvbuff_t * tvb , int offset , guint32 num_rows , struct CPMSetBindingsIn * bindingsin , struct rows_data * rowsin , gboolean is64bit , proto_tree * parent_tree , const char * fmt , ... ) {
 proto_tree * tree ;
 proto_item * item ;
 guint32 num ;
 const char * txt ;
 va_list ap ;
 va_start ( ap , fmt ) ;
 txt = wmem_strdup_vprintf ( wmem_packet_scope ( ) , fmt , ap ) ;
 va_end ( ap ) ;
 tree = proto_tree_add_subtree ( parent_tree , tvb , offset , 0 , ett_GetRowsRow , & item , txt ) ;
 for ( num = 0 ;
 num < num_rows ;
 ++ num ) {
 guint32 col ;
 proto_tree * row_tree ;
 row_tree = proto_tree_add_subtree_format ( tree , tvb , offset , 0 , ett_GetRowsRow , NULL , "Row[%d]" , num ) ;
 for ( col = 0 ;
 col < bindingsin -> ccolumns ;
 col ++ ) {
 parse_RowsBufferCol ( tvb , offset , num , col , bindingsin , rowsin , is64bit , row_tree , "Col[%d]" , col ) ;
 }
 }
 return offset ;
 }