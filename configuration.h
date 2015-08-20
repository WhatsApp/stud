/**
 * configuration.h
 *
 * Author: Brane F. Gracnar
 *
 */

#include <sys/types.h>

#ifdef USE_SHARED_CACHE
  #include "shctx.h"

  #ifndef MAX_SHCUPD_PEERS
    #define MAX_SHCUPD_PEERS 15
  #endif

typedef struct shcupd_peer_opt {
     char *ip;
     char *port;
} shcupd_peer_opt;

#endif

typedef enum {
    ENC_TLS,
    ENC_SSL
} ENC_TYPE;

typedef enum {
    SSL_SERVER,
    SSL_CLIENT
} PROXY_MODE;

struct stud_config_addr {
    struct stud_config_addr* next;
    char* IP;
    char* PORT;
    struct addrinfo *addr;
    int prefix_bits;
};

/* configuration structure */
struct __stud_config {
    ENC_TYPE ETYPE;
    PROXY_MODE PMODE;
    int WRITE_IP_OCTET;
    int WRITE_PROXY_LINE;
    char *CHROOT;
    int UID;
    int GID;
    struct stud_config_addr* FRONTADDR;
    struct stud_config_addr* BACKADDR;
    struct stud_config_addr* BACKADDR_DEFAULT;
    long NCORES;
    char *CERT_FILE;
    char *CERT_FILE_SHA2;
    char *CIPHER_SUITE;
    char *ENGINE;
    int BACKLOG;
#ifdef USE_SHARED_CACHE
    int SHARED_CACHE;
    char *SHCUPD_IP;
    char *SHCUPD_PORT;
    shcupd_peer_opt SHCUPD_PEERS[MAX_SHCUPD_PEERS+1];
    char *SHCUPD_MCASTIF;
    char *SHCUPD_MCASTTTL;
#endif
    int QUIET;
    int VERBOSE;
    int SYSLOG;
    int SYSLOG_FACILITY;
    int TCP_KEEPALIVE_TIME;
    int DAEMONIZE;
    int PREFER_SERVER_CIPHERS;
    int BACKEND_CONNECT_TIMEOUT;
    int SSL_HANDSHAKE_TIMEOUT;
    int RECV_BUFSIZE;
    int SEND_BUFSIZE;
    char* LOG_FILENAME;
    int RING_SLOTS;
    int RING_DATA_LEN;
    int BACKEND_CONNECT;
    int REQUIRE_PEER_CERT;
    unsigned char* PINNED_CERT_DIGEST;
    char *CA_FILE;
    int MAX_DH_USES;
};

typedef struct __stud_config stud_config;

char * config_error_get (void);
stud_config * config_new (void);
void config_destroy (stud_config *cfg);
int config_file_parse (char *file, stud_config *cfg);
void config_parse_cli(int argc, char **argv, stud_config *cfg);
int config_same_subnet (const struct sockaddr* s1, const struct sockaddr* s2, int prefix_bits);
