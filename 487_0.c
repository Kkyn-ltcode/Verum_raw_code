void mime_init ( ) {
 static int init = 1 ;
 if ( init ) {
 init = 0 ;
 hdrtoken_init ( ) ;
 day_names_dfa = new DFA ;
 day_names_dfa -> compile ( day_names , SIZEOF ( day_names ) , RE_CASE_INSENSITIVE ) ;
 month_names_dfa = new DFA ;
 month_names_dfa -> compile ( month_names , SIZEOF ( month_names ) , RE_CASE_INSENSITIVE ) ;
 MIME_FIELD_ACCEPT = hdrtoken_string_to_wks ( "Accept" ) ;
 MIME_FIELD_ACCEPT_CHARSET = hdrtoken_string_to_wks ( "Accept-Charset" ) ;
 MIME_FIELD_ACCEPT_ENCODING = hdrtoken_string_to_wks ( "Accept-Encoding" ) ;
 MIME_FIELD_ACCEPT_LANGUAGE = hdrtoken_string_to_wks ( "Accept-Language" ) ;
 MIME_FIELD_ACCEPT_RANGES = hdrtoken_string_to_wks ( "Accept-Ranges" ) ;
 MIME_FIELD_AGE = hdrtoken_string_to_wks ( "Age" ) ;
 MIME_FIELD_ALLOW = hdrtoken_string_to_wks ( "Allow" ) ;
 MIME_FIELD_APPROVED = hdrtoken_string_to_wks ( "Approved" ) ;
 MIME_FIELD_AUTHORIZATION = hdrtoken_string_to_wks ( "Authorization" ) ;
 MIME_FIELD_BYTES = hdrtoken_string_to_wks ( "Bytes" ) ;
 MIME_FIELD_CACHE_CONTROL = hdrtoken_string_to_wks ( "Cache-Control" ) ;
 MIME_FIELD_CLIENT_IP = hdrtoken_string_to_wks ( "Client-ip" ) ;
 MIME_FIELD_CONNECTION = hdrtoken_string_to_wks ( "Connection" ) ;
 MIME_FIELD_CONTENT_BASE = hdrtoken_string_to_wks ( "Content-Base" ) ;
 MIME_FIELD_CONTENT_ENCODING = hdrtoken_string_to_wks ( "Content-Encoding" ) ;
 MIME_FIELD_CONTENT_LANGUAGE = hdrtoken_string_to_wks ( "Content-Language" ) ;
 MIME_FIELD_CONTENT_LENGTH = hdrtoken_string_to_wks ( "Content-Length" ) ;
 MIME_FIELD_CONTENT_LOCATION = hdrtoken_string_to_wks ( "Content-Location" ) ;
 MIME_FIELD_CONTENT_MD5 = hdrtoken_string_to_wks ( "Content-MD5" ) ;
 MIME_FIELD_CONTENT_RANGE = hdrtoken_string_to_wks ( "Content-Range" ) ;
 MIME_FIELD_CONTENT_TYPE = hdrtoken_string_to_wks ( "Content-Type" ) ;
 MIME_FIELD_CONTROL = hdrtoken_string_to_wks ( "Control" ) ;
 MIME_FIELD_COOKIE = hdrtoken_string_to_wks ( "Cookie" ) ;
 MIME_FIELD_DATE = hdrtoken_string_to_wks ( "Date" ) ;
 MIME_FIELD_DISTRIBUTION = hdrtoken_string_to_wks ( "Distribution" ) ;
 MIME_FIELD_ETAG = hdrtoken_string_to_wks ( "Etag" ) ;
 MIME_FIELD_EXPECT = hdrtoken_string_to_wks ( "Expect" ) ;
 MIME_FIELD_EXPIRES = hdrtoken_string_to_wks ( "Expires" ) ;
 MIME_FIELD_FOLLOWUP_TO = hdrtoken_string_to_wks ( "Followup-To" ) ;
 MIME_FIELD_FROM = hdrtoken_string_to_wks ( "From" ) ;
 MIME_FIELD_HOST = hdrtoken_string_to_wks ( "Host" ) ;
 MIME_FIELD_IF_MATCH = hdrtoken_string_to_wks ( "If-Match" ) ;
 MIME_FIELD_IF_MODIFIED_SINCE = hdrtoken_string_to_wks ( "If-Modified-Since" ) ;
 MIME_FIELD_IF_NONE_MATCH = hdrtoken_string_to_wks ( "If-None-Match" ) ;
 MIME_FIELD_IF_RANGE = hdrtoken_string_to_wks ( "If-Range" ) ;
 MIME_FIELD_IF_UNMODIFIED_SINCE = hdrtoken_string_to_wks ( "If-Unmodified-Since" ) ;
 MIME_FIELD_KEEP_ALIVE = hdrtoken_string_to_wks ( "Keep-Alive" ) ;
 MIME_FIELD_KEYWORDS = hdrtoken_string_to_wks ( "Keywords" ) ;
 MIME_FIELD_LAST_MODIFIED = hdrtoken_string_to_wks ( "Last-Modified" ) ;
 MIME_FIELD_LINES = hdrtoken_string_to_wks ( "Lines" ) ;
 MIME_FIELD_LOCATION = hdrtoken_string_to_wks ( "Location" ) ;
 MIME_FIELD_MAX_FORWARDS = hdrtoken_string_to_wks ( "Max-Forwards" ) ;
 MIME_FIELD_MESSAGE_ID = hdrtoken_string_to_wks ( "Message-ID" ) ;
 MIME_FIELD_NEWSGROUPS = hdrtoken_string_to_wks ( "Newsgroups" ) ;
 MIME_FIELD_ORGANIZATION = hdrtoken_string_to_wks ( "Organization" ) ;
 MIME_FIELD_PATH = hdrtoken_string_to_wks ( "Path" ) ;
 MIME_FIELD_PRAGMA = hdrtoken_string_to_wks ( "Pragma" ) ;
 MIME_FIELD_PROXY_AUTHENTICATE = hdrtoken_string_to_wks ( "Proxy-Authenticate" ) ;
 MIME_FIELD_PROXY_AUTHORIZATION = hdrtoken_string_to_wks ( "Proxy-Authorization" ) ;
 MIME_FIELD_PROXY_CONNECTION = hdrtoken_string_to_wks ( "Proxy-Connection" ) ;
 MIME_FIELD_PUBLIC = hdrtoken_string_to_wks ( "Public" ) ;
 MIME_FIELD_RANGE = hdrtoken_string_to_wks ( "Range" ) ;
 MIME_FIELD_REFERENCES = hdrtoken_string_to_wks ( "References" ) ;
 MIME_FIELD_REFERER = hdrtoken_string_to_wks ( "Referer" ) ;
 MIME_FIELD_REPLY_TO = hdrtoken_string_to_wks ( "Reply-To" ) ;
 MIME_FIELD_RETRY_AFTER = hdrtoken_string_to_wks ( "Retry-After" ) ;
 MIME_FIELD_SENDER = hdrtoken_string_to_wks ( "Sender" ) ;
 MIME_FIELD_SERVER = hdrtoken_string_to_wks ( "Server" ) ;
 MIME_FIELD_SET_COOKIE = hdrtoken_string_to_wks ( "Set-Cookie" ) ;
 MIME_FIELD_STRICT_TRANSPORT_SECURITY = hdrtoken_string_to_wks ( "Strict-Transport-Security" ) ;
 MIME_FIELD_SUBJECT = hdrtoken_string_to_wks ( "Subject" ) ;
 MIME_FIELD_SUMMARY = hdrtoken_string_to_wks ( "Summary" ) ;
 MIME_FIELD_TE = hdrtoken_string_to_wks ( "TE" ) ;
 MIME_FIELD_TRANSFER_ENCODING = hdrtoken_string_to_wks ( "Transfer-Encoding" ) ;
 MIME_FIELD_UPGRADE = hdrtoken_string_to_wks ( "Upgrade" ) ;
 MIME_FIELD_USER_AGENT = hdrtoken_string_to_wks ( "User-Agent" ) ;
 MIME_FIELD_VARY = hdrtoken_string_to_wks ( "Vary" ) ;
 MIME_FIELD_VIA = hdrtoken_string_to_wks ( "Via" ) ;
 MIME_FIELD_WARNING = hdrtoken_string_to_wks ( "Warning" ) ;
 MIME_FIELD_WWW_AUTHENTICATE = hdrtoken_string_to_wks ( "Www-Authenticate" ) ;
 MIME_FIELD_XREF = hdrtoken_string_to_wks ( "Xref" ) ;
 MIME_FIELD_ATS_INTERNAL = hdrtoken_string_to_wks ( "@Ats-Internal" ) ;
 MIME_FIELD_X_ID = hdrtoken_string_to_wks ( "X-ID" ) ;
 MIME_FIELD_X_FORWARDED_FOR = hdrtoken_string_to_wks ( "X-Forwarded-For" ) ;
 MIME_FIELD_SEC_WEBSOCKET_KEY = hdrtoken_string_to_wks ( "Sec-WebSocket-Key" ) ;
 MIME_FIELD_SEC_WEBSOCKET_VERSION = hdrtoken_string_to_wks ( "Sec-WebSocket-Version" ) ;
 MIME_FIELD_HTTP2_SETTINGS = hdrtoken_string_to_wks ( "HTTP2-Settings" ) ;
 MIME_LEN_ACCEPT = hdrtoken_wks_to_length ( MIME_FIELD_ACCEPT ) ;
 MIME_LEN_ACCEPT_CHARSET = hdrtoken_wks_to_length ( MIME_FIELD_ACCEPT_CHARSET ) ;
 MIME_LEN_ACCEPT_ENCODING = hdrtoken_wks_to_length ( MIME_FIELD_ACCEPT_ENCODING ) ;
 MIME_LEN_ACCEPT_LANGUAGE = hdrtoken_wks_to_length ( MIME_FIELD_ACCEPT_LANGUAGE ) ;
 MIME_LEN_ACCEPT_RANGES = hdrtoken_wks_to_length ( MIME_FIELD_ACCEPT_RANGES ) ;
 MIME_LEN_AGE = hdrtoken_wks_to_length ( MIME_FIELD_AGE ) ;
 MIME_LEN_ALLOW = hdrtoken_wks_to_length ( MIME_FIELD_ALLOW ) ;
 MIME_LEN_APPROVED = hdrtoken_wks_to_length ( MIME_FIELD_APPROVED ) ;
 MIME_LEN_AUTHORIZATION = hdrtoken_wks_to_length ( MIME_FIELD_AUTHORIZATION ) ;
 MIME_LEN_BYTES = hdrtoken_wks_to_length ( MIME_FIELD_BYTES ) ;
 MIME_LEN_CACHE_CONTROL = hdrtoken_wks_to_length ( MIME_FIELD_CACHE_CONTROL ) ;
 MIME_LEN_CLIENT_IP = hdrtoken_wks_to_length ( MIME_FIELD_CLIENT_IP ) ;
 MIME_LEN_CONNECTION = hdrtoken_wks_to_length ( MIME_FIELD_CONNECTION ) ;
 MIME_LEN_CONTENT_BASE = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_BASE ) ;
 MIME_LEN_CONTENT_ENCODING = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_ENCODING ) ;
 MIME_LEN_CONTENT_LANGUAGE = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_LANGUAGE ) ;
 MIME_LEN_CONTENT_LENGTH = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_LENGTH ) ;
 MIME_LEN_CONTENT_LOCATION = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_LOCATION ) ;
 MIME_LEN_CONTENT_MD5 = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_MD5 ) ;
 MIME_LEN_CONTENT_RANGE = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_RANGE ) ;
 MIME_LEN_CONTENT_TYPE = hdrtoken_wks_to_length ( MIME_FIELD_CONTENT_TYPE ) ;
 MIME_LEN_CONTROL = hdrtoken_wks_to_length ( MIME_FIELD_CONTROL ) ;
 MIME_LEN_COOKIE = hdrtoken_wks_to_length ( MIME_FIELD_COOKIE ) ;
 MIME_LEN_DATE = hdrtoken_wks_to_length ( MIME_FIELD_DATE ) ;
 MIME_LEN_DISTRIBUTION = hdrtoken_wks_to_length ( MIME_FIELD_DISTRIBUTION ) ;
 MIME_LEN_ETAG = hdrtoken_wks_to_length ( MIME_FIELD_ETAG ) ;
 MIME_LEN_EXPECT = hdrtoken_wks_to_length ( MIME_FIELD_EXPECT ) ;
 MIME_LEN_EXPIRES = hdrtoken_wks_to_length ( MIME_FIELD_EXPIRES ) ;
 MIME_LEN_FOLLOWUP_TO = hdrtoken_wks_to_length ( MIME_FIELD_FOLLOWUP_TO ) ;
 MIME_LEN_FROM = hdrtoken_wks_to_length ( MIME_FIELD_FROM ) ;
 MIME_LEN_HOST = hdrtoken_wks_to_length ( MIME_FIELD_HOST ) ;
 MIME_LEN_IF_MATCH = hdrtoken_wks_to_length ( MIME_FIELD_IF_MATCH ) ;
 MIME_LEN_IF_MODIFIED_SINCE = hdrtoken_wks_to_length ( MIME_FIELD_IF_MODIFIED_SINCE ) ;
 MIME_LEN_IF_NONE_MATCH = hdrtoken_wks_to_length ( MIME_FIELD_IF_NONE_MATCH ) ;
 MIME_LEN_IF_RANGE = hdrtoken_wks_to_length ( MIME_FIELD_IF_RANGE ) ;
 MIME_LEN_IF_UNMODIFIED_SINCE = hdrtoken_wks_to_length ( MIME_FIELD_IF_UNMODIFIED_SINCE ) ;
 MIME_LEN_KEEP_ALIVE = hdrtoken_wks_to_length ( MIME_FIELD_KEEP_ALIVE ) ;
 MIME_LEN_KEYWORDS = hdrtoken_wks_to_length ( MIME_FIELD_KEYWORDS ) ;
 MIME_LEN_LAST_MODIFIED = hdrtoken_wks_to_length ( MIME_FIELD_LAST_MODIFIED ) ;
 MIME_LEN_LINES = hdrtoken_wks_to_length ( MIME_FIELD_LINES ) ;
 MIME_LEN_LOCATION = hdrtoken_wks_to_length ( MIME_FIELD_LOCATION ) ;
 MIME_LEN_MAX_FORWARDS = hdrtoken_wks_to_length ( MIME_FIELD_MAX_FORWARDS ) ;
 MIME_LEN_MESSAGE_ID = hdrtoken_wks_to_length ( MIME_FIELD_MESSAGE_ID ) ;
 MIME_LEN_NEWSGROUPS = hdrtoken_wks_to_length ( MIME_FIELD_NEWSGROUPS ) ;
 MIME_LEN_ORGANIZATION = hdrtoken_wks_to_length ( MIME_FIELD_ORGANIZATION ) ;
 MIME_LEN_PATH = hdrtoken_wks_to_length ( MIME_FIELD_PATH ) ;
 MIME_LEN_PRAGMA = hdrtoken_wks_to_length ( MIME_FIELD_PRAGMA ) ;
 MIME_LEN_PROXY_AUTHENTICATE = hdrtoken_wks_to_length ( MIME_FIELD_PROXY_AUTHENTICATE ) ;
 MIME_LEN_PROXY_AUTHORIZATION = hdrtoken_wks_to_length ( MIME_FIELD_PROXY_AUTHORIZATION ) ;
 MIME_LEN_PROXY_CONNECTION = hdrtoken_wks_to_length ( MIME_FIELD_PROXY_CONNECTION ) ;
 MIME_LEN_PUBLIC = hdrtoken_wks_to_length ( MIME_FIELD_PUBLIC ) ;
 MIME_LEN_RANGE = hdrtoken_wks_to_length ( MIME_FIELD_RANGE ) ;
 MIME_LEN_REFERENCES = hdrtoken_wks_to_length ( MIME_FIELD_REFERENCES ) ;
 MIME_LEN_REFERER = hdrtoken_wks_to_length ( MIME_FIELD_REFERER ) ;
 MIME_LEN_REPLY_TO = hdrtoken_wks_to_length ( MIME_FIELD_REPLY_TO ) ;
 MIME_LEN_RETRY_AFTER = hdrtoken_wks_to_length ( MIME_FIELD_RETRY_AFTER ) ;
 MIME_LEN_SENDER = hdrtoken_wks_to_length ( MIME_FIELD_SENDER ) ;
 MIME_LEN_SERVER = hdrtoken_wks_to_length ( MIME_FIELD_SERVER ) ;
 MIME_LEN_SET_COOKIE = hdrtoken_wks_to_length ( MIME_FIELD_SET_COOKIE ) ;
 MIME_LEN_STRICT_TRANSPORT_SECURITY = hdrtoken_wks_to_length ( MIME_FIELD_STRICT_TRANSPORT_SECURITY ) ;
 MIME_LEN_SUBJECT = hdrtoken_wks_to_length ( MIME_FIELD_SUBJECT ) ;
 MIME_LEN_SUMMARY = hdrtoken_wks_to_length ( MIME_FIELD_SUMMARY ) ;
 MIME_LEN_TE = hdrtoken_wks_to_length ( MIME_FIELD_TE ) ;
 MIME_LEN_TRANSFER_ENCODING = hdrtoken_wks_to_length ( MIME_FIELD_TRANSFER_ENCODING ) ;
 MIME_LEN_UPGRADE = hdrtoken_wks_to_length ( MIME_FIELD_UPGRADE ) ;
 MIME_LEN_USER_AGENT = hdrtoken_wks_to_length ( MIME_FIELD_USER_AGENT ) ;
 MIME_LEN_VARY = hdrtoken_wks_to_length ( MIME_FIELD_VARY ) ;
 MIME_LEN_VIA = hdrtoken_wks_to_length ( MIME_FIELD_VIA ) ;
 MIME_LEN_WARNING = hdrtoken_wks_to_length ( MIME_FIELD_WARNING ) ;
 MIME_LEN_WWW_AUTHENTICATE = hdrtoken_wks_to_length ( MIME_FIELD_WWW_AUTHENTICATE ) ;
 MIME_LEN_XREF = hdrtoken_wks_to_length ( MIME_FIELD_XREF ) ;
 MIME_LEN_ATS_INTERNAL = hdrtoken_wks_to_length ( MIME_FIELD_ATS_INTERNAL ) ;
 MIME_LEN_X_ID = hdrtoken_wks_to_length ( MIME_FIELD_X_ID ) ;
 MIME_LEN_X_FORWARDED_FOR = hdrtoken_wks_to_length ( MIME_FIELD_X_FORWARDED_FOR ) ;
 MIME_LEN_SEC_WEBSOCKET_KEY = hdrtoken_wks_to_length ( MIME_FIELD_SEC_WEBSOCKET_KEY ) ;
 MIME_LEN_SEC_WEBSOCKET_VERSION = hdrtoken_wks_to_length ( MIME_FIELD_SEC_WEBSOCKET_VERSION ) ;
 MIME_LEN_HTTP2_SETTINGS = hdrtoken_wks_to_length ( MIME_FIELD_HTTP2_SETTINGS ) ;
 MIME_WKSIDX_ACCEPT = hdrtoken_wks_to_index ( MIME_FIELD_ACCEPT ) ;
 MIME_WKSIDX_ACCEPT_CHARSET = hdrtoken_wks_to_index ( MIME_FIELD_ACCEPT_CHARSET ) ;
 MIME_WKSIDX_ACCEPT_ENCODING = hdrtoken_wks_to_index ( MIME_FIELD_ACCEPT_ENCODING ) ;
 MIME_WKSIDX_ACCEPT_LANGUAGE = hdrtoken_wks_to_index ( MIME_FIELD_ACCEPT_LANGUAGE ) ;
 MIME_WKSIDX_ACCEPT_RANGES = hdrtoken_wks_to_index ( MIME_FIELD_ACCEPT_RANGES ) ;
 MIME_WKSIDX_AGE = hdrtoken_wks_to_index ( MIME_FIELD_AGE ) ;
 MIME_WKSIDX_ALLOW = hdrtoken_wks_to_index ( MIME_FIELD_ALLOW ) ;
 MIME_WKSIDX_APPROVED = hdrtoken_wks_to_index ( MIME_FIELD_APPROVED ) ;
 MIME_WKSIDX_AUTHORIZATION = hdrtoken_wks_to_index ( MIME_FIELD_AUTHORIZATION ) ;
 MIME_WKSIDX_BYTES = hdrtoken_wks_to_index ( MIME_FIELD_BYTES ) ;
 MIME_WKSIDX_CACHE_CONTROL = hdrtoken_wks_to_index ( MIME_FIELD_CACHE_CONTROL ) ;
 MIME_WKSIDX_CLIENT_IP = hdrtoken_wks_to_index ( MIME_FIELD_CLIENT_IP ) ;
 MIME_WKSIDX_CONNECTION = hdrtoken_wks_to_index ( MIME_FIELD_CONNECTION ) ;
 MIME_WKSIDX_CONTENT_BASE = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_BASE ) ;
 MIME_WKSIDX_CONTENT_ENCODING = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_ENCODING ) ;
 MIME_WKSIDX_CONTENT_LANGUAGE = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_LANGUAGE ) ;
 MIME_WKSIDX_CONTENT_LENGTH = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_LENGTH ) ;
 MIME_WKSIDX_CONTENT_LOCATION = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_LOCATION ) ;
 MIME_WKSIDX_CONTENT_MD5 = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_MD5 ) ;
 MIME_WKSIDX_CONTENT_RANGE = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_RANGE ) ;
 MIME_WKSIDX_CONTENT_TYPE = hdrtoken_wks_to_index ( MIME_FIELD_CONTENT_TYPE ) ;
 MIME_WKSIDX_CONTROL = hdrtoken_wks_to_index ( MIME_FIELD_CONTROL ) ;
 MIME_WKSIDX_COOKIE = hdrtoken_wks_to_index ( MIME_FIELD_COOKIE ) ;
 MIME_WKSIDX_DATE = hdrtoken_wks_to_index ( MIME_FIELD_DATE ) ;
 MIME_WKSIDX_DISTRIBUTION = hdrtoken_wks_to_index ( MIME_FIELD_DISTRIBUTION ) ;
 MIME_WKSIDX_ETAG = hdrtoken_wks_to_index ( MIME_FIELD_ETAG ) ;
 MIME_WKSIDX_EXPECT = hdrtoken_wks_to_index ( MIME_FIELD_EXPECT ) ;
 MIME_WKSIDX_EXPIRES = hdrtoken_wks_to_index ( MIME_FIELD_EXPIRES ) ;
 MIME_WKSIDX_FOLLOWUP_TO = hdrtoken_wks_to_index ( MIME_FIELD_FOLLOWUP_TO ) ;
 MIME_WKSIDX_FROM = hdrtoken_wks_to_index ( MIME_FIELD_FROM ) ;
 MIME_WKSIDX_HOST = hdrtoken_wks_to_index ( MIME_FIELD_HOST ) ;
 MIME_WKSIDX_IF_MATCH = hdrtoken_wks_to_index ( MIME_FIELD_IF_MATCH ) ;
 MIME_WKSIDX_IF_MODIFIED_SINCE = hdrtoken_wks_to_index ( MIME_FIELD_IF_MODIFIED_SINCE ) ;
 MIME_WKSIDX_IF_NONE_MATCH = hdrtoken_wks_to_index ( MIME_FIELD_IF_NONE_MATCH ) ;
 MIME_WKSIDX_IF_RANGE = hdrtoken_wks_to_index ( MIME_FIELD_IF_RANGE ) ;
 MIME_WKSIDX_IF_UNMODIFIED_SINCE = hdrtoken_wks_to_index ( MIME_FIELD_IF_UNMODIFIED_SINCE ) ;
 MIME_WKSIDX_KEEP_ALIVE = hdrtoken_wks_to_index ( MIME_FIELD_KEEP_ALIVE ) ;
 MIME_WKSIDX_KEYWORDS = hdrtoken_wks_to_index ( MIME_FIELD_KEYWORDS ) ;
 MIME_WKSIDX_LAST_MODIFIED = hdrtoken_wks_to_index ( MIME_FIELD_LAST_MODIFIED ) ;
 MIME_WKSIDX_LINES = hdrtoken_wks_to_index ( MIME_FIELD_LINES ) ;
 MIME_WKSIDX_LOCATION = hdrtoken_wks_to_index ( MIME_FIELD_LOCATION ) ;
 MIME_WKSIDX_MAX_FORWARDS = hdrtoken_wks_to_index ( MIME_FIELD_MAX_FORWARDS ) ;
 MIME_WKSIDX_MESSAGE_ID = hdrtoken_wks_to_index ( MIME_FIELD_MESSAGE_ID ) ;
 MIME_WKSIDX_NEWSGROUPS = hdrtoken_wks_to_index ( MIME_FIELD_NEWSGROUPS ) ;
 MIME_WKSIDX_ORGANIZATION = hdrtoken_wks_to_index ( MIME_FIELD_ORGANIZATION ) ;
 MIME_WKSIDX_PATH = hdrtoken_wks_to_index ( MIME_FIELD_PATH ) ;
 MIME_WKSIDX_PRAGMA = hdrtoken_wks_to_index ( MIME_FIELD_PRAGMA ) ;
 MIME_WKSIDX_PROXY_AUTHENTICATE = hdrtoken_wks_to_index ( MIME_FIELD_PROXY_AUTHENTICATE ) ;
 MIME_WKSIDX_PROXY_AUTHORIZATION = hdrtoken_wks_to_index ( MIME_FIELD_PROXY_AUTHORIZATION ) ;
 MIME_WKSIDX_PROXY_CONNECTION = hdrtoken_wks_to_index ( MIME_FIELD_PROXY_CONNECTION ) ;
 MIME_WKSIDX_PUBLIC = hdrtoken_wks_to_index ( MIME_FIELD_PUBLIC ) ;
 MIME_WKSIDX_RANGE = hdrtoken_wks_to_index ( MIME_FIELD_RANGE ) ;
 MIME_WKSIDX_REFERENCES = hdrtoken_wks_to_index ( MIME_FIELD_REFERENCES ) ;
 MIME_WKSIDX_REFERER = hdrtoken_wks_to_index ( MIME_FIELD_REFERER ) ;
 MIME_WKSIDX_REPLY_TO = hdrtoken_wks_to_index ( MIME_FIELD_REPLY_TO ) ;
 MIME_WKSIDX_RETRY_AFTER = hdrtoken_wks_to_index ( MIME_FIELD_RETRY_AFTER ) ;
 MIME_WKSIDX_SENDER = hdrtoken_wks_to_index ( MIME_FIELD_SENDER ) ;
 MIME_WKSIDX_SERVER = hdrtoken_wks_to_index ( MIME_FIELD_SERVER ) ;
 MIME_WKSIDX_SET_COOKIE = hdrtoken_wks_to_index ( MIME_FIELD_SET_COOKIE ) ;
 MIME_WKSIDX_STRICT_TRANSPORT_SECURITY = hdrtoken_wks_to_index ( MIME_FIELD_STRICT_TRANSPORT_SECURITY ) ;
 MIME_WKSIDX_SUBJECT = hdrtoken_wks_to_index ( MIME_FIELD_SUBJECT ) ;
 MIME_WKSIDX_SUMMARY = hdrtoken_wks_to_index ( MIME_FIELD_SUMMARY ) ;
 MIME_WKSIDX_TE = hdrtoken_wks_to_index ( MIME_FIELD_TE ) ;
 MIME_WKSIDX_TRANSFER_ENCODING = hdrtoken_wks_to_index ( MIME_FIELD_TRANSFER_ENCODING ) ;
 MIME_WKSIDX_UPGRADE = hdrtoken_wks_to_index ( MIME_FIELD_UPGRADE ) ;
 MIME_WKSIDX_USER_AGENT = hdrtoken_wks_to_index ( MIME_FIELD_USER_AGENT ) ;
 MIME_WKSIDX_VARY = hdrtoken_wks_to_index ( MIME_FIELD_VARY ) ;
 MIME_WKSIDX_VIA = hdrtoken_wks_to_index ( MIME_FIELD_VIA ) ;
 MIME_WKSIDX_WARNING = hdrtoken_wks_to_index ( MIME_FIELD_WARNING ) ;
 MIME_WKSIDX_WWW_AUTHENTICATE = hdrtoken_wks_to_index ( MIME_FIELD_WWW_AUTHENTICATE ) ;
 MIME_WKSIDX_XREF = hdrtoken_wks_to_index ( MIME_FIELD_XREF ) ;
 MIME_WKSIDX_X_ID = hdrtoken_wks_to_index ( MIME_FIELD_X_ID ) ;
 MIME_WKSIDX_X_FORWARDED_FOR = hdrtoken_wks_to_index ( MIME_FIELD_X_FORWARDED_FOR ) ;
 MIME_WKSIDX_SEC_WEBSOCKET_KEY = hdrtoken_wks_to_index ( MIME_FIELD_SEC_WEBSOCKET_KEY ) ;
 MIME_WKSIDX_SEC_WEBSOCKET_VERSION = hdrtoken_wks_to_index ( MIME_FIELD_SEC_WEBSOCKET_VERSION ) ;
 MIME_WKSIDX_HTTP2_SETTINGS = hdrtoken_wks_to_index ( MIME_FIELD_HTTP2_SETTINGS ) ;
 MIME_VALUE_BYTES = hdrtoken_string_to_wks ( "bytes" ) ;
 MIME_VALUE_CHUNKED = hdrtoken_string_to_wks ( "chunked" ) ;
 MIME_VALUE_CLOSE = hdrtoken_string_to_wks ( "close" ) ;
 MIME_VALUE_COMPRESS = hdrtoken_string_to_wks ( "compress" ) ;
 MIME_VALUE_DEFLATE = hdrtoken_string_to_wks ( "deflate" ) ;
 MIME_VALUE_GZIP = hdrtoken_string_to_wks ( "gzip" ) ;
 MIME_VALUE_IDENTITY = hdrtoken_string_to_wks ( "identity" ) ;
 MIME_VALUE_KEEP_ALIVE = hdrtoken_string_to_wks ( "keep-alive" ) ;
 MIME_VALUE_MAX_AGE = hdrtoken_string_to_wks ( "max-age" ) ;
 MIME_VALUE_MAX_STALE = hdrtoken_string_to_wks ( "max-stale" ) ;
 MIME_VALUE_MIN_FRESH = hdrtoken_string_to_wks ( "min-fresh" ) ;
 MIME_VALUE_MUST_REVALIDATE = hdrtoken_string_to_wks ( "must-revalidate" ) ;
 MIME_VALUE_NONE = hdrtoken_string_to_wks ( "none" ) ;
 MIME_VALUE_NO_CACHE = hdrtoken_string_to_wks ( "no-cache" ) ;
 MIME_VALUE_NO_STORE = hdrtoken_string_to_wks ( "no-store" ) ;
 MIME_VALUE_NO_TRANSFORM = hdrtoken_string_to_wks ( "no-transform" ) ;
 MIME_VALUE_ONLY_IF_CACHED = hdrtoken_string_to_wks ( "only-if-cached" ) ;
 MIME_VALUE_PRIVATE = hdrtoken_string_to_wks ( "private" ) ;
 MIME_VALUE_PROXY_REVALIDATE = hdrtoken_string_to_wks ( "proxy-revalidate" ) ;
 MIME_VALUE_PUBLIC = hdrtoken_string_to_wks ( "public" ) ;
 MIME_VALUE_S_MAXAGE = hdrtoken_string_to_wks ( "s-maxage" ) ;
 MIME_VALUE_NEED_REVALIDATE_ONCE = hdrtoken_string_to_wks ( "need-revalidate-once" ) ;
 MIME_VALUE_WEBSOCKET = hdrtoken_string_to_wks ( "websocket" ) ;
 MIME_VALUE_H2C = hdrtoken_string_to_wks ( MIME_UPGRADE_H2C_TOKEN ) ;
 mime_init_date_format_table ( ) ;
 mime_init_cache_control_cooking_masks ( ) ;
 }
 }