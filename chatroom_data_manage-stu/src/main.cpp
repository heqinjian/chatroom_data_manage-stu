#include"mysql.h"
#include<iostream>
#include"user.h"
#include"group.h"
#include"groupuser.h"
#include"friendmodel.h"
#include"groupmodel.h"
#include"usermodel.h"
#include"offlinemessagemodel.h"
#include<map>
#include<vector>
#include<string>
using namespace ChatRoom;
using namespace std;
// 定义ANSI转义码的颜色
const std::string RED = "\033[31m";      // 红色
const std::string GREEN = "\033[32m";    // 绿色
const std::string YELLOW = "\033[33m";   // 黄色
const std::string BLUE = "\033[34m";     // 蓝色
const std::string YRED = "\033[35m";     // 洋红色
const std::string QING = "\033[36m";     // 青色
const std::string WHITE = "\033[37m";     // 白色
const std::string RESET = "\033[0m";     // 重置颜色
enum Managetype{
    QUERY = 1,
    ADD,
    DELETE,
    UPDATE,
    STATISTIC   //统计
};
void print_menu(){
    cout << "============欢迎来带东软校友通数据管理系统=================" << endl;
    cout << WHITE <<"请选择您的操作:"<< RESET <<endl;
    cout << YELLOW <<"1.信息查询" << RESET << endl;
    cout << YELLOW <<"2.信息添加" << RESET << endl;
    cout << YELLOW <<"3.信息删除" << RESET << endl;
    cout << YELLOW <<"4.信息更新" << RESET << endl;
    cout << YELLOW <<"5.信息统计" << RESET << endl;
    cout << "=========================================================" << endl;
    cout << BLUE <<"请输入:"<<RESET;
};
void UserDataManage(){
    UserModel userModel;
    print_menu();
    int choice = 0;
    cin >> choice;
    switch(choice){
        case QUERY:
        {
            cout << WHITE <<"请输入待查询的用户信息(用户名,输入all为查询全部):"<< RESET <<endl;
            string name;
            cin>>name;
            cout<<YELLOW<<"查询结果为:"<<RESET<<endl;
            vector<User> vec;
            vec = userModel.query(name);
            if(!vec.empty()){
                for(auto& user:vec){
                    if(user.getId() != -1){
                        cout<<GREEN<<"user id:"<<user.getId()<<" ";
                        cout<<GREEN<<"user name:"<<user.getName()<<" ";
                        cout<<GREEN<<"user State:"<<user.getState()<<RESET<<endl;
                    }else{
                        cout<<RED<<"用户未找到,请检查!"<<RESET<<endl;
                    }
                }
            }else{
                cout<<RED<<"用户未找到,请检查！"<<RESET<<endl;
            }
        }
        break;
        case ADD:
        {
            string name,password;
            cout<<YELLOW<<"应输入用户名:"<<endl;
            cin>>name;
            cout<<"请输入用户密码:"<<RESET<<endl;
            cin>>password;
            User user;
            user.setName(name);
            user.setPwd(password);
            bool res = userModel.insert(user);
            if(res){
                cout<<GREEN<<"用户插入成功！"<<RESET<<endl;
            }else{
                cout<<RED<<"用户插入失败!"<<RESET<<endl;
            }    
        }
        break;
        case DELETE:
        {
            int user_id = 0;
            cout<<YELLOW<<"请输入待删除的用户id:"<<RESET<<endl;
            cin>>user_id;  
            bool res = userModel.deleteUser(user_id);
            if(res){
                cout<<GREEN<<"用户删除成功"<<RESET<<endl;
            }else{
                cout<<RED<<"用户删除失败!"<<RESET<<endl;
            }    
        }
        break;
        case UPDATE:
        {
            int user_id = 0,chioce = 0;
            string info;
            bool res;
            User user;
            cout<<YELLOW<<"请输入待更新的用户id:"<<endl;
            cin>>user_id;
            user.setId(user_id);
            cin.get();
            cout<<WHITE<<"请选择您要更新的内容:"<<RESET<<endl;
            cout << YELLOW <<"1.更新用户名" << RESET << endl;
            cout << YELLOW <<"2.更新状态" << RESET << endl;
            cin>>chioce;
            cin.get(); //吸收换行符
            if(1 == chioce){
                cout<<WHITE<<"请输入新的用户名:"<<RESET<<endl;
                cin>>info;
                user.setName(info);
                res = userModel.updateName(user);
            }
            else if(2 == chioce){
                cout<<WHITE<<"请输入新的用户状态:"<<RESET<<endl;
                cin>>info;
                user.setState(info);
                res = userModel.updateState(user);
            }else{
                cout<<RED<<"输入有误"<<endl;
                break;
            }
            if(res){
                cout<<GREEN<<"信息更新成功"<<RESET<<endl;
            }else{
                cout<<RED<<"信息更细失败!"<<RESET<<endl;
            }    
        }
        break;
        case STATISTIC:
        {
            int count = userModel.userCount();
            if(count == -1){
                cout<<RED<<"查询出错"<<RESET<<endl;
            }else{
                cout<<GREEN<<"当前系统用户数量为:"<<count<<RESET<<endl;
            }
        }
        break;
        default:
        cout<<RED<<"输入有误！"<<RESET<<endl;
        break;
    }

}
void FriendDataManage(){
    
}
void GroupDataManage(){
    
}
void OfflineDataManage(){
    
}
int main(){
    int choice = 0;
    while(1){
        // 显示首页面菜单、查询、插入、删除、更新
        cout << "===========欢迎来到东软校友通数据管理系统===============" << endl;
        cout << WHITE <<"请选择您的操作："<< RESET <<endl;
        cout << YELLOW <<"1.用户信息管理" << RESET << endl;
        cout << YELLOW <<"2.好友信息管理" << RESET << endl;
        cout << YELLOW <<"3.群组信息管理" << RESET << endl;
        cout << YELLOW <<"4.离线信息管理" << RESET << endl;
        cout << "=====================================================" << endl;
        cout << BLUE <<"请输入:"<<RESET;
        cin >>choice;
        if(-1 == choice){
            cout<<YELLOW<<"退出系统"<<RESET<<endl;
            break;
        }
        cin.get();// 读掉缓冲区的回车
        switch(choice)
        {
            case 1: //用户数据管理
                UserDataManage();
                break;
            case 2: //好友数据管理
                FriendDataManage();
                break;
            case 3: //群组数据管理
                GroupDataManage();
                break;
            case 4: //离线消息管理
                OfflineDataManage();
                break;
            default:
                cout<<RED<<"input error"<<RESET<<endl;
                cin.clear();  //异常输入时,cin会输出错误标记，通过clear将其清除
                cin.ignore(100,'\n'); //清空缓冲区
                break;
        }
        
    }
    return 0;
}
