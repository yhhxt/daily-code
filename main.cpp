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
        cout<<"����ʱ�䣺����-��-ʱ-�֣�";
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
        cout<<"�����복�ƺţ�";
        in>>s.plate_number;
        cout<<"���ʱ�䣺����-��-ʱ-�֣�";
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
        out<<setw(8)<<s.plate_number<<setw(8)<<s.month1<<"��"<<s.day1<<"��"<<s.hour1<<"ʱ"<<s.minues1<<"��";
        if (s.month2!=0)
            out<<setw(8)<<s.month2<<"��"<<s.day2<<"��"<<s.hour2<<"ʱ"<<s.minues2<<"��"<<setw(8)<<s.hour<<"Сʱ"<<s.minues<<"����"<<setw(8)<<s.pay;
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
        cout<<"ͣ��ʱ����"<<hour<<"Сʱ"<<minues<<"����"<<endl;
        if ((hour==0)&&(minues<30)) pay=0;
        if (hour>=1)
        {
            if (minues<30) pay=hour*5;
            if (minues>30) pay=(hour+1)*5;
        }
        if (pay==0) cout<<"����ͣ��δ��30���ӣ����շ���"<<endl;
        else cout<<"�����"<<pay<<"Ԫ"<<endl;
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
    fstream fout("ͣ������ϵͳ.txt",ios::in|ios::binary);
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
        fstream fout("ͣ������ϵͳ.txt",ios::in|ios::app|ios::binary);
        if (!fout)
        {
            cout<<"���ļ�ʧ�ܣ�"<<endl;
            return;
        }
        int c=0;
        cin>>ca;
        while (ca.day1>31||ca.day1<=0||ca.month1<=0||ca.month1>12||ca.hour1>=24||ca.hour1<0||ca.minues1>=60||ca.minues1<0)
        {
            cout<<"�������ʱ�����,���������복����Ϣ:"<<endl;
            cin>>ca;
        }
        if (isre(ca.plate_number)==1)
        {
            cout<<ca.plate_number<<endl;
            cout<<"���ʱ��:"<<ca.month1<<"��"<<ca.day1<<"��"<<ca.hour1<<"ʱ"<<ca.minues1<<"��"<<endl;
            fout.write((char*)&ca,sizeof(car));
            fout.close();
            c=1;
        }
        if (c==0)
        {
            cout<<"¼������ó�����ͣ�ڳ�����!"<<endl;
        }
        system("pause");
    }
    if (isfull()==0)
    {
        cout<<"�ǳ���Ǹ��ͣ����λ���������޷�ͣ������ȴ����������뿪���ٽ���ͣ����"<<endl;
        system("pause");
    }
}
int isfull()
{
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::binary);
    car ca;
    int k,n;
    k=0;
    n=10;
    fin.seekp(0*sizeof(car),ios::beg);��
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
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::out|ios::binary);
    car ca;
    cout<<"�����복�ƺţ�";
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
                cout<<"��������ʱ�����(ʱ���ʽ������߳���ʱ���������ʱ��),���������복����Ϣ:"<<endl;
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
        cout<<"���ƺ�����������²���"<<endl;
        system("pause");
    }
}
void found_number()
{
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::binary);
    car ca;
    char a[10];
    cout<<"�����복�����ƺŽ��в�ѯ��";
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
            cout<<"    ����"<<"        ���ʱ��"<<"          ����ʱ��"<<"           ͣ��ʱ��"<<"    ͣ����(��λ:Ԫ)"<<endl;
            cout<<ca;
        }
        fin.read((char*)&ca,sizeof(car));
    }
    if (k==0)
    {
        cout<<"û�иó�����ͣ����¼"<<endl;
    }
    if (k==1)
    {
        cout<<"�ܹ��鵽�ó���"<<n<<"��ͣ����¼��������ʱ��Ϊ�գ�����ó�����ͣ�ڳ�����"<<endl;
    }
    system("pause");
}
void found_time()
{
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::binary);
    car ca;
    cout<<"���������ʱ����в�ѯ(��-��):";
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
            cout<<"    ����"<<"        ���ʱ��"<<"          ����ʱ��"<<"           ͣ��ʱ��"<<"    ͣ����(��λ:Ԫ)"<<endl;
            cout<<ca;
        }
        fin.read((char*)&ca,sizeof(car));
    }
    if (k==0)
    {
        cout<<"û�и��յ�ͣ����¼"<<endl;
    }
    if (k==1)
    {
        cout<<"�ܹ��鵽���յ�"<<n<<"��ͣ����¼��������ʱ��Ϊ�գ�����ó�����ͣ�ڳ�����"<<endl;
    }
    system("pause");
}
void stopping()
{
    system("cls");
    cout<<"***********��ӭ���복����Ϣ¼��ϵͳ***********"<<endl;
    cout<<"**********************************************"<<endl;
    cout<<"***********�������      �밴1��***********"<<endl;
    cout<<"***********��������      �밴2��***********"<<endl;
    cout<<"***********�����ϲ�Ŀ¼  �밴3��***********"<<endl;
    int y;
    cin>>y;
    while (y<1||y>3)
    {
        cout<<"ѡ���������Ч�����������룺"<<endl;
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
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::binary);
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
    cout<<"ʣ�೵λ��:"<<n-k<<endl;
    system("pause");
}
void Now()
{
    fstream fin("ͣ������ϵͳ.txt",ios::in|ios::binary);
    car ca;
    fin.read((char*)&ca,sizeof (car));
    cout<<"    ����"<<"        ���ʱ��"<<"          ����ʱ��"<<"           ͣ��ʱ��"<<"    ͣ����(��λ:Ԫ)"<<endl;
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
    cout<<"***********��ӭ���복����Ϣ¼��ϵͳ***********"<<endl;
    cout<<"**********************************************"<<endl;
    cout<<"***********������Ϣ��ѯ      �밴1��**********"<<endl;
    cout<<"***********������λ��ѯ      �밴2��**********"<<endl;
    cout<<"******ͣ����¼��ѯ(����)     �밴3��**********"<<endl;
    cout<<"******ͣ����¼��ѯ(����)     �밴4��**********"<<endl;
    int z;
    cin>>z;
    while (z<1||z>4)
    {
        cout<<"ѡ���������Ч�����������룺"<<endl;
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
            cout<<"***********��ӭ����ͣ������ϵͳ***************"<<endl;
            cout<<"**********************************************"<<endl;
            cout<<"***********ͣ��������Ϣ¼��ϵͳ     �밴1��***"<<endl;
            cout<<"***********����Ա��Ϣ��ѯϵͳ    �����빤�ţ�*"<<endl;
            int x;
            cin>>x;
            while (x!=1&&x!=2019)
            {
                cout<<"ѡ���������Ч�����������룺"<<endl;
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
