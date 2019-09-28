#include <iostream>
#include <time.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <iomanip>
using namespace std;
class car;
istream& operator>>(istream &in,car &s);
ostream& operator<<(ostream &out,car &s);
int isfull();
class car
{
private :
    int day,day1,day2;
    int month,month1,month2;
    int hour,hour1,hour2;
    int minues,minues1,minues2;
    int pay;
    char plate_number[10];
public:
    int GetTime1()
    {
        cout<<"出库时间：（月-日-时-分）";
        cin>>month2;
        return month2;
    }
    int GetTime2()
    {
        cin>>day2;
        return day2;
    }
    int GetTime3()
    {
        cin>>hour2;

        return hour2;
    }
    int GetTime4()
    {
        cin>>minues2;
        return minues2;
    }

    friend istream& operator>>(istream &in,car &s)
    {
        cout<<"请输入车牌号：";
        in>>s.plate_number;
        cout<<"入库时间：（月-日-时-分）";
        in>>s.month1;
        in>>s.day1;

        in>>s.hour1;

        in>>s.minues1;

        s.day2=0;
        s.month2=0;
        s.hour2=0;
        s.minues2=0;
        cout<<endl;
        return in;
    }
    friend ostream& operator<<(ostream &out,car &s)
    {
        out<<setw(8)<<s.plate_number<<setw(8)<<s.month1<<"月"<<s.day1<<"日"<<s.hour1<<"时"<<s.minues1<<"分";
        if (s.month2!=0)
            out<<setw(8)<<s.month2<<"月"<<s.day2<<"日"<<s.hour2<<"时"<<s.minues2<<"分"<<setw(8)<<s.hour<<"小时"<<s.minues<<"分钟"<<setw(8)<<s.pay;
        cout<<endl;
        return out;
    }
    int  payment()
    {
        month=month2-month1;
        day=day2-day1+30*month;
        hour=hour2-hour1+day*24;
        minues=minues2-minues1;
        if (minues<0)
        {
            hour--;
            minues=60+minues;
        }
        cout<<"停车时长："<<hour<<"小时"<<minues<<"分钟"<<endl;
        if ((hour==0)&&(minues<30)) pay=0;
        if (hour>=1)
        {
            if (minues<30) pay=hour*5;
            if (minues>30) pay=(hour+1)*5;
        }
        if (pay==0) cout<<"本次停车未满30分钟，免收费用"<<endl;
        else cout<<"请缴纳"<<pay<<"元"<<endl;
        return pay;

    }
    friend int isfull();
    friend void add();
    friend void account();
    friend void Time();
    friend void Now();
    friend int isre(char *a);
    friend void found_number();
    friend void found_time();
};
int isre(char *a)
{
    fstream fout("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    int b=1;
    fout.read((char*)&ca,sizeof(car));
    while (!fout.eof())
    {
        if (strcmp(a,ca.plate_number)==0&&ca.day2==0&&ca.month2==0) b=0;
        if (strcmp(a,ca.plate_number)==0&&ca.day2==0&&ca.month2!=0) b=1;
        fout.read((char*)&ca,sizeof (car));
    }
    return b;
}
void add()
{
    if (isfull()==1)
    {
        car ca;
        fstream fout("停车管理系统.txt",ios::in|ios::app|ios::binary);
        if (!fout)
        {
            cout<<"打开文件失败！"<<endl;
            return;
        }
        int c=0;
        cin>>ca;
        while (ca.day1>31||ca.day1<=0||ca.month1<=0||ca.month1>12||ca.hour1>=24||ca.hour1<0||ca.minues1>=60||ca.minues1<0)
        {
            cout<<"车辆入库时间错误,请重新输入车辆信息:"<<endl;
            cin>>ca;
        }
        if (isre(ca.plate_number)==1)
        {
            cout<<ca.plate_number<<endl;
            cout<<"入库时间:"<<ca.month1<<"月"<<ca.day1<<"日"<<ca.hour1<<"时"<<ca.minues1<<"分"<<endl;
            fout.write((char*)&ca,sizeof(car));
            fout.close();
            c=1;
        }
        if (c==0)
        {
            cout<<"录入出错，该车辆已停在车库内!"<<endl;
        }
        system("pause");
    }
    if (isfull()==0)
    {
        cout<<"非常抱歉，停车场位置已满，无法停车，请等待其他车辆离开后再进入停车场"<<endl;
        system("pause");
    }
}
int isfull()
{
    fstream fin("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    int k,n;
    k=0;
    n=10;
    fin.seekp(0*sizeof(car),ios::beg);好
    fin.read((char*)&ca,sizeof(car));
    while (!fin.eof())
    {
        if (ca.day2==0&&ca.month2==0&&ca.hour2==0&&ca.minues2==0)k++;
        fin.read((char*)&ca,sizeof(car));
    }
    if (k>=n) return 0;
    else return 1;
}

void account()
{
    fstream fin("停车管理系统.txt",ios::in|ios::out|ios::binary);
    car ca;
    cout<<"请输入车牌号：";
    char a[10];
    cin>>a;
    int i=0;
    int c=0;

    fin.read((char*)&ca,sizeof(car));
    while (!fin.eof())
    {
        if (strcmp(a,ca.plate_number)==0&&ca.day2==0)
        {
            c=1;
            ca.month2=ca.GetTime1();
            ca.day2=ca.GetTime2();
            ca.hour2=ca.GetTime3();
            ca.minues2=ca.GetTime4();
            while (ca.day2>31||ca.day2<=0||ca.month2<=0||ca.month2>12||ca.hour2>=24||ca.hour2<0||ca.minues2>=60||ca.minues2<0||ca.month1>ca.month2||(ca.month1==ca.month2&&ca.day1>ca.day2)||(ca.month1==ca.month2&&ca.day1==ca.day2&&ca.hour1>ca.hour2)||(ca.month1==ca.month2&&ca.day1==ca.day2&&ca.hour1==ca.hour2&&ca.minues1>ca.minues2))
            {
                cout<<"车辆出库时间错误(时间格式错误或者出库时间早于入库时间),请重新输入车辆信息:"<<endl;
                ca.month2=ca.GetTime1();
                ca.day2=ca.GetTime2();
                ca.hour2=ca.GetTime3();
                ca.minues2=ca.GetTime4();
            }
            ca.pay=ca.payment();
            fin.seekp(i*sizeof(car),ios::beg);
            fin.write((char*)&ca,sizeof(car));

            cout<<ca;
            system("pause");
            break;
        }
        i++;
        fin.read((char*)&ca,sizeof(car));
    }
    fin.close();
    while (c!=1)
    {
        cout<<"车牌号码错误！请重新操作"<<endl;
        system("pause");
    }
}
void found_number()
{
    fstream fin("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    char a[10];
    cout<<"请输入车辆车牌号进行查询：";
    cin>>a;
    int n,k;
    k=0;
    n=0;
    fin.read((char*)&ca,sizeof(car));
    while (!fin.eof())
    {
        if (strcmp(a,ca.plate_number)==0)
        {
            n++;
            k=1;
            cout<<"    车牌"<<"        入库时间"<<"          出库时间"<<"           停车时间"<<"    停车费(单位:元)"<<endl;
            cout<<ca;
        }
        fin.read((char*)&ca,sizeof(car));
    }
    if (k==0)
    {
        cout<<"没有该车辆的停车记录"<<endl;
    }
    if (k==1)
    {
        cout<<"总共查到该车的"<<n<<"条停车记录，若出库时间为空，代表该车辆仍停在车库里"<<endl;
    }
    system("pause");
}
void found_time()
{
    fstream fin("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    cout<<"请输入入库时间进行查询(月-日):";
    int a,b;
    int n,k;
    k=0;
    n=0;
    cin>>a>>b;
    fin.read((char*)&ca,sizeof(car));
    while (!fin.eof())
    {
        if (ca.month1==a&&ca.day1==b)
        {
            n++;
            k=1;
            cout<<"    车牌"<<"        入库时间"<<"          出库时间"<<"           停车时间"<<"    停车费(单位:元)"<<endl;
            cout<<ca;
        }
        fin.read((char*)&ca,sizeof(car));
    }
    if (k==0)
    {
        cout<<"没有该日的停车记录"<<endl;
    }
    if (k==1)
    {
        cout<<"总共查到该日的"<<n<<"条停车记录，若出库时间为空，代表该车辆仍停在车库里"<<endl;
    }
    system("pause");
}
void stopping()
{
    system("cls");
    cout<<"***********欢迎进入车辆信息录入系统***********"<<endl;
    cout<<"**********************************************"<<endl;
    cout<<"***********汽车入库      请按1：***********"<<endl;
    cout<<"***********汽车出库      请按2：***********"<<endl;
    cout<<"***********返回上层目录  请按3：***********"<<endl;
    int y;
    cin>>y;
    while (y<1||y>3)
    {
        cout<<"选择的数据无效，请重新输入："<<endl;
        cin>>y;
    }
    cout<<endl;
    switch (y)
    {
    case 1:
        add();
        break;
    case 2:
        account();
        break;
    case 3:
        return ;
    }
}
void Time()
{
    fstream fin("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    int k,n;
    k=0;
    n=10;
    fin.seekp(0*sizeof(car),ios::beg);
    fin.read((char*)&ca,sizeof(car));
    while (!fin.eof())
    {
        if (ca.day2==0&&ca.month2==0&&ca.hour2==0&&ca.minues2==0)k++;
        fin.read((char*)&ca,sizeof(car));
    }
    cout<<"剩余车位数:"<<n-k<<endl;
    system("pause");
}
void Now()
{
    fstream fin("停车管理系统.txt",ios::in|ios::binary);
    car ca;
    fin.read((char*)&ca,sizeof (car));
    cout<<"    车牌"<<"        入库时间"<<"          出库时间"<<"           停车时间"<<"    停车费(单位:元)"<<endl;
    while (!fin.eof())
    {
        cout<<ca;
        fin.read((char*)&ca,sizeof (car));
    }
    fin.close();
    system("pause");
}
void manage()
{
    system("cls");
    cout<<"***********欢迎进入车辆信息录入系统***********"<<endl;
    cout<<"**********************************************"<<endl;
    cout<<"***********汽车信息查询      请按1：**********"<<endl;
    cout<<"***********车场空位查询      请按2：**********"<<endl;
    cout<<"******停车记录查询(车牌)     请按3：**********"<<endl;
    cout<<"******停车记录查询(日期)     请按4：**********"<<endl;
    int z;
    cin>>z;
    while (z<1||z>4)
    {
        cout<<"选择的数据无效，请重新输入："<<endl;
        cin>>z;
    }
    cout<<endl;
    switch(z)
    {
    case 1 :
        Now();
        break;
    case 2 :
        Time();
        break;
    case 3 :
        found_number();
        break;
    case 4 :
        found_time();
        break;
    }
}
int main()
{
    while (1)
    {
        system("cls");
        {
            cout<<"***********欢迎进入停车管理系统***************"<<endl;
            cout<<"**********************************************"<<endl;
            cout<<"***********停车车辆信息录入系统     请按1：***"<<endl;
            cout<<"***********管理员信息查询系统    请输入工号：*"<<endl;
            int x;
            cin>>x;
            while (x!=1&&x!=2019)
            {
                cout<<"选择的数据无效，请重新输入："<<endl;
                cin>>x;
            }
            cout<<endl;
            switch(x)
            {
            case 1:
                stopping();
                break;
            case 2019:
                manage();
                break;
            }
        }
    }
}
