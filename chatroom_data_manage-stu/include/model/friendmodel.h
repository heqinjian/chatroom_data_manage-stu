#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include "user.h"
#include <vector>
using namespace std;
namespace ChatRoom{
// 维护好友信息的操作接口方法
class FriendModel
{
public:
    // 添加好友关系

    // 返回用户好友列表
    vector<User> query(int userid);

    //删除好友

    //统计好友个数
};
}
#endif
