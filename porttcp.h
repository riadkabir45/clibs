#ifndef __PORTTCP__
#define __PORTTCP__

#ifdef _WIN32

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

class TCP{
    private:
        WSADATA wsa;
        SOCKET sLink,sClient;
        struct sockaddr_in sDescrip,cClient;
        bool server;
        bool bInit = false;
    public:
        TCP(){
            if (WSAStartup(MAKEWORD(2,2),&wsa) == 0)
                bInit = true;
        }

        bool addr(const char *ip,int port){
            bool name = false;
            if((sLink = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
                return false;
            for(int i=0;ip[i]!='\0';i++)
                if((ip[i]  < '0' or ip[i] > '9') and ip[i] != '.'){
                    name = true;
                    break;
                }
            if(name){
                struct hostent *url;
	            struct in_addr **addr_list;
                if ( (url = gethostbyname( ip ) ) == NULL) 
                    return false;
                addr_list = (struct in_addr **) url->h_addr_list;
                for(int i = 0; addr_list[i] != NULL; i++)
                    sDescrip.sin_addr.s_addr = inet_addr(inet_ntoa(*addr_list[i]));
            }else
                sDescrip.sin_addr.s_addr = inet_addr(ip);
            sDescrip.sin_family = AF_INET;
	        sDescrip.sin_port = htons( port );
            server = false;
            return true;
        }

        bool addr(int port){
            if((sLink = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
                return false;
                sDescrip.sin_addr.s_addr = INADDR_ANY;
	            sDescrip.sin_family = AF_INET;
	            sDescrip.sin_port = htons( port );
                server = true;
            return true;
        }

        bool link(){
            if (connect(sLink , (struct sockaddr *)&sDescrip , sizeof(sDescrip)) < 0)
                return false;
            return true;
        }

        bool tbind(){
            if( bind(sLink ,(struct sockaddr *)&sDescrip , sizeof(sDescrip)) == SOCKET_ERROR)
                return false;
            listen(sLink , 3);
            return true;
        }

        bool taccept(){
            int c = sizeof(struct sockaddr_in);
	        sClient = accept(sLink , (struct sockaddr *)&cClient, &c);
            if (sClient == INVALID_SOCKET)
                return false;
            return true;
        }

        bool tsend(const char *message,int size){
            if(server){
                if( send(sClient , message , size , 0) < 0)
                    return false;

            }else{
                if( send(sLink , message , size , 0) < 0)
                    return false;
            }
            return true;
        }

        bool trecv(char *reply,int size){
            int recv_size = 0;
            if(server){
                if((recv_size = recv(sClient , reply , size , 0)) == SOCKET_ERROR)
                    return false;
            }else{
                if((recv_size = recv(sLink , reply , size , 0)) == SOCKET_ERROR)
                    return false;
            }
            reply[recv_size] = '\0';
            return true;
        }

        bool close(){
            if(closesocket(sLink) != 0)
                return false;
            return true;
        }
};

#else

#include<sys/socket.h>

class TCP{
        private:
        public:
};

#endif

#endif
