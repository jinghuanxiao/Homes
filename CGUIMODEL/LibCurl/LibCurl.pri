INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
DEFINES += HAVE_CONFIG_H

DISTFILES += \
    $$PWD/checksrc.pl \
    $$PWD/mk-ca-bundle.pl \
    $$PWD/firefox-db2pem.sh \
    $$PWD/libcurl.plist \
    $$PWD/curl_config.h.in \
    $$PWD/libcurl.vers.in \
    $$PWD/mk-ca-bundle.vbs \
    $$PWD/curl_config.h.cmake \
    $$PWD/CMakeLists.txt

HEADERS += \
    $$PWD/curl/curl.h \
    $$PWD/curl/curlver.h \
    $$PWD/curl/easy.h \
    $$PWD/curl/mprintf.h \
    $$PWD/curl/multi.h \
    $$PWD/curl/stdcheaders.h \
    $$PWD/curl/system.h \
    $$PWD/curl/typecheck-gcc.h \
    $$PWD/curl/urlapi.h \
    $$PWD/vauth/digest.h \
    $$PWD/vauth/ntlm.h \
    $$PWD/vauth/vauth.h \
    $$PWD/vquic/ngtcp2.h \
    $$PWD/vquic/quiche.h \
    $$PWD/vtls/gskit.h \
    $$PWD/vtls/gtls.h \
    $$PWD/vtls/mbedtls.h \
    $$PWD/vtls/mesalink.h \
    $$PWD/vtls/nssg.h \
    $$PWD/vtls/openssl.h \
    $$PWD/vtls/polarssl.h \
    $$PWD/vtls/polarssl_threadlock.h \
    $$PWD/vtls/schannel.h \
    $$PWD/vtls/sectransp.h \
    $$PWD/vtls/vtls.h \
    $$PWD/vtls/wolfssl.h \
    $$PWD/altsvc.h \
    $$PWD/amigaos.h \
    $$PWD/arpa_telnet.h \
    $$PWD/asyn.h \
    $$PWD/config-amigaos.h \
    $$PWD/config-dos.h \
    $$PWD/config-mac.h \
    $$PWD/config-os400.h \
    $$PWD/config-plan9.h \
    $$PWD/config-riscos.h \
    $$PWD/config-symbian.h \
    $$PWD/config-tpf.h \
    $$PWD/config-vxworks.h \
    $$PWD/config-win32.h \
    $$PWD/config-win32ce.h \
    $$PWD/conncache.h \
    $$PWD/connect.h \
    $$PWD/content_encoding.h \
    $$PWD/cookie.h \
    $$PWD/curl_addrinfo.h \
    $$PWD/curl_base64.h \
    $$PWD/curl_ctype.h \
    $$PWD/curl_des.h \
    $$PWD/curl_endian.h \
    $$PWD/curl_fnmatch.h \
    $$PWD/curl_get_line.h \
    $$PWD/curl_gethostname.h \
    $$PWD/curl_gssapi.h \
    $$PWD/curl_hmac.h \
    $$PWD/curl_ldap.h \
    $$PWD/curl_md4.h \
    $$PWD/curl_md5.h \
    $$PWD/curl_memory.h \
    $$PWD/curl_memrchr.h \
    $$PWD/curl_multibyte.h \
    $$PWD/curl_ntlm_core.h \
    $$PWD/curl_ntlm_wb.h \
    $$PWD/curl_path.h \
    $$PWD/curl_printf.h \
    $$PWD/curl_range.h \
    $$PWD/curl_rtmp.h \
    $$PWD/curl_sasl.h \
    $$PWD/curl_sec.h \
    $$PWD/curl_setup.h \
    $$PWD/curl_setup_once.h \
    $$PWD/curl_sha256.h \
    $$PWD/curl_sspi.h \
    $$PWD/curl_threads.h \
    $$PWD/curlx.h \
    $$PWD/dict.h \
    $$PWD/doh.h \
    $$PWD/dotdot.h \
    $$PWD/easyif.h \
    $$PWD/escape.h \
    $$PWD/file.h \
    $$PWD/fileinfo.h \
    $$PWD/formdata.h \
    $$PWD/ftp.h \
    $$PWD/ftplistparser.h \
    $$PWD/getinfo.h \
    $$PWD/gopher.h \
    $$PWD/hash.h \
    $$PWD/hostcheck.h \
    $$PWD/hostip.h \
    $$PWD/http.h \
    $$PWD/http2.h \
    $$PWD/http_chunks.h \
    $$PWD/http_digest.h \
    $$PWD/http_negotiate.h \
    $$PWD/http_ntlm.h \
    $$PWD/http_proxy.h \
    $$PWD/if2ip.h \
    $$PWD/imap.h \
    $$PWD/inet_ntop.h \
    $$PWD/inet_pton.h \
    $$PWD/libcurl.rc \
    $$PWD/llist.h \
    $$PWD/memdebug.h \
    $$PWD/mime.h \
    $$PWD/multihandle.h \
    $$PWD/multiif.h \
    $$PWD/netrc.h \
    $$PWD/non-ascii.h \
    $$PWD/nonblock.h \
    $$PWD/parsedate.h \
    $$PWD/pingpong.h \
    $$PWD/pop3.h \
    $$PWD/progress.h \
    $$PWD/psl.h \
    $$PWD/quic.h \
    $$PWD/rand.h \
    $$PWD/rtsp.h \
    $$PWD/select.h \
    $$PWD/sendf.h \
    $$PWD/setopt.h \
    $$PWD/setup-os400.h \
    $$PWD/setup-vms.h \
    $$PWD/share.h \
    $$PWD/sigpipe.h \
    $$PWD/slist.h \
    $$PWD/smb.h \
    $$PWD/smtp.h \
    $$PWD/sockaddr.h \
    $$PWD/socks.h \
    $$PWD/speedcheck.h \
    $$PWD/splay.h \
    $$PWD/ssh.h \
    $$PWD/strcase.h \
    $$PWD/strdup.h \
    $$PWD/strerror.h \
    $$PWD/strtok.h \
    $$PWD/strtoofft.h \
    $$PWD/system_win32.h \
    $$PWD/telnet.h \
    $$PWD/tftp.h \
    $$PWD/timeval.h \
    $$PWD/transfer.h \
    $$PWD/url.h \
    $$PWD/urlapi-int.h \
    $$PWD/urldata.h \
    $$PWD/warnless.h \
    $$PWD/wildcard.h \
    $$PWD/x509asn1.h \
    $$PWD/curl_config.h

SOURCES += \
    $$PWD/vauth/cleartext.c \
    $$PWD/vauth/cram.c \
    $$PWD/vauth/digest.c \
    $$PWD/vauth/digest_sspi.c \
    $$PWD/vauth/krb5_gssapi.c \
    $$PWD/vauth/krb5_sspi.c \
    $$PWD/vauth/ntlm.c \
    $$PWD/vauth/ntlm_sspi.c \
    $$PWD/vauth/oauth2.c \
    $$PWD/vauth/spnego_gssapi.c \
    $$PWD/vauth/spnego_sspi.c \
    $$PWD/vauth/vauth.c \
    $$PWD/vquic/ngtcp2.c \
    $$PWD/vquic/quiche.c \
    $$PWD/vssh/libssh.c \
    $$PWD/vssh/libssh2.c \
    $$PWD/vtls/gskit.c \
    $$PWD/vtls/gtls.c \
    $$PWD/vtls/mbedtls.c \
    $$PWD/vtls/mesalink.c \
    $$PWD/vtls/nss.c \
    $$PWD/vtls/openssl.c \
    $$PWD/vtls/polarssl.c \
    $$PWD/vtls/polarssl_threadlock.c \
    $$PWD/vtls/schannel.c \
    $$PWD/vtls/schannel_verify.c \
    $$PWD/vtls/sectransp.c \
    $$PWD/vtls/vtls.c \
    $$PWD/vtls/wolfssl.c \
    $$PWD/altsvc.c \
    $$PWD/amigaos.c \
    $$PWD/asyn-ares.c \
    $$PWD/asyn-thread.c \
    $$PWD/base64.c \
    $$PWD/conncache.c \
    $$PWD/connect.c \
    $$PWD/content_encoding.c \
    $$PWD/cookie.c \
    $$PWD/curl_addrinfo.c \
    $$PWD/curl_ctype.c \
    $$PWD/curl_des.c \
    $$PWD/curl_endian.c \
    $$PWD/curl_fnmatch.c \
    $$PWD/curl_get_line.c \
    $$PWD/curl_gethostname.c \
    $$PWD/curl_gssapi.c \
    $$PWD/curl_memrchr.c \
    $$PWD/curl_multibyte.c \
    $$PWD/curl_ntlm_core.c \
    $$PWD/curl_ntlm_wb.c \
    $$PWD/curl_path.c \
    $$PWD/curl_range.c \
    $$PWD/curl_rtmp.c \
    $$PWD/curl_sasl.c \
    $$PWD/curl_sspi.c \
    $$PWD/curl_threads.c \
    $$PWD/dict.c \
    $$PWD/doh.c \
    $$PWD/dotdot.c \
    $$PWD/easy.c \
    $$PWD/escape.c \
    $$PWD/file.c \
    $$PWD/fileinfo.c \
    $$PWD/formdata.c \
    $$PWD/ftp.c \
    $$PWD/ftplistparser.c \
    $$PWD/getenv.c \
    $$PWD/getinfo.c \
    $$PWD/gopher.c \
    $$PWD/hash.c \
    $$PWD/hmac.c \
    $$PWD/hostasyn.c \
    $$PWD/hostcheck.c \
    $$PWD/hostip.c \
    $$PWD/hostip4.c \
    $$PWD/hostip6.c \
    $$PWD/hostsyn.c \
    $$PWD/http.c \
    $$PWD/http2.c \
    $$PWD/http_chunks.c \
    $$PWD/http_digest.c \
    $$PWD/http_negotiate.c \
    $$PWD/http_ntlm.c \
    $$PWD/http_proxy.c \
    $$PWD/idn_win32.c \
    $$PWD/if2ip.c \
    $$PWD/imap.c \
    $$PWD/inet_ntop.c \
    $$PWD/inet_pton.c \
    $$PWD/krb5.c \
    $$PWD/ldap.c \
    $$PWD/llist.c \
    $$PWD/md4.c \
    $$PWD/md5.c \
    $$PWD/memdebug.c \
    $$PWD/mime.c \
    $$PWD/mprintf.c \
    $$PWD/multi.c \
    $$PWD/netrc.c \
    $$PWD/non-ascii.c \
    $$PWD/nonblock.c \
    $$PWD/nwlib.c \
    $$PWD/nwos.c \
    $$PWD/openldap.c \
    $$PWD/parsedate.c \
    $$PWD/pingpong.c \
    $$PWD/pop3.c \
    $$PWD/progress.c \
    $$PWD/psl.c \
    $$PWD/rand.c \
    $$PWD/rtsp.c \
    $$PWD/security.c \
    $$PWD/select.c \
    $$PWD/sendf.c \
    $$PWD/setopt.c \
    $$PWD/sha256.c \
    $$PWD/share.c \
    $$PWD/slist.c \
    $$PWD/smb.c \
    $$PWD/smtp.c \
    $$PWD/socks.c \
    $$PWD/socks_gssapi.c \
    $$PWD/socks_sspi.c \
    $$PWD/speedcheck.c \
    $$PWD/splay.c \
    $$PWD/strcase.c \
    $$PWD/strdup.c \
    $$PWD/strerror.c \
    $$PWD/strtok.c \
    $$PWD/strtoofft.c \
    $$PWD/system_win32.c \
    $$PWD/telnet.c \
    $$PWD/tftp.c \
    $$PWD/timeval.c \
    $$PWD/transfer.c \
    $$PWD/url.c \
    $$PWD/urlapi.c \
    $$PWD/version.c \
    $$PWD/warnless.c \
    $$PWD/wildcard.c \
    $$PWD/x509asn1.c
