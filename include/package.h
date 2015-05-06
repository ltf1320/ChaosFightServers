#ifndef __H_PACKAGE__
#define __H_PACKAGE__


#include "base.h"


struct PackHead{
	int32_t len;
	int32_t type;
};

const int HEAD_LEN=sizeof(PackHead);


#define LOGIN_REQ 0
struct LoginReq{
	char account[10]; 	//1-9λӢ�������˺�
	char password[16];  //6-15λӢ����������
};

#define LOGIN_RSP 1
struct LoginRsp{
	bool isPass;	//�Ƿ��¼�ɹ�
	int signature; 	//ǩ��
};

#define REGISTER_REQ 2
struct RegisterReq{
	char account[10];
	char password[16];
};

#define REGISTER_RSP 3
struct RegisterRsp{
	bool isSuccess;  //ע���Ƿ�ɹ�
};

#define MATCH_REQ 4
struct MatchReq{
	int signature;
};

#define MATCH_RSP 5
struct MatchRsp{
	int player_id;
	int game_server_port;	  //��Ϸ�����������˿ں�
	char game_server_ip[16];  //��Ϸ����������ip
};

#define CHOOSE_HERO_REQ 6
struct ChooseHeroReq{
	int role_id; 	//��ɫid
	int signature;
};


#define ___placeholder___ 7

struct NetPlayerInfo{
	char player_nick_name[10];
	int role_id;
};

#define GAME_READY_RSP 8
struct GameReadyRsp{
	int seed; //�������
	struct PlayerInfo info[6]; //player0-5����Ϣ
};

struct KeyDownStatus{
	bool u;
	bool d;
	bool l;
	bool r;
	bool attack;
	bool skill_A;
	bool skill_B;
	int genius_mask;
};

#define SYNC_OP_REQ 9
struct SyncOpReq{
	int signature;
	int frame_num;
	struct KeyDownStatus op;
	int genius_mask;       //�츳����
};

#define SYNC_OP_RSP 10
struct SyncOpRsp{
	KeyDownStatus ops[6];  //player0-5�Ĳ�����Ϣ
	int frame_num;
};

#define GAME_RES_REQ 11
struct GameResReq{
	int signature;
	bool isVictory;
};

struct GameResult{
	int current_rating;
	int change;
};

#define GAME_RES_RSP 12
struct GameResRsp{
	struct GameResult result_set[6]; //player0-5 ս������rating��Ϣ
};

#define GAME_ENTER_REQ 14
struct GameEnterReq{
	int signature;
};

#define GET_RATING_REQ 15
struct GetRatingReq{
	int signature;
};

#define GET_RATING_RSP 16
struct GetRatingRsp{
	int rating;
};


extern void pack_send(int fd,const char *msg,int len,int type);
extern int pack_recv(int fd,char *&buf);




#endif
