#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(700,500);
    connect(ui->pushButton_equal,&QPushButton::clicked,this,&MainWindow::startcalculate);
    connect(ui->pushButton_lcm,&QPushButton::clicked,this,&MainWindow::on_pushButton_lcm_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
double MainWindow::bin(QString expression,int l){//二进制转为十进制
    double ans1=0,ans2=0;
    int i=0;
    bool ok=true;
    QString num="";
    if(l>=expression.length()){
        wrong="表达式错误";
        return 0;
    }
    if(expression.at(l)=='-'){
        num.append('-');
        l++;
    }
    while(l<expression.length()&&(expression.at(l)>='0'&&expression.at(l)<='9'||expression.at(l)=='.')){
        num.append(expression.at(l));
        l++;
    }
    num.toDouble(&ok);
    nextpos=l;
    if(!ok)wrong="不合法的二进制数";
    else{
        for(;i<num.length()&&num.at(i)!='.';i++){
            if(num.at(i)=='1'||num.at(i)=='0')ans1=ans1*2+(int)num.at(i).toLatin1()-48;
            else wrong="不合法的二进制数";
        }
        for(int j=num.length()-1;j>i;j--){
            if(num.at(j)=='0'||num.at(j)=='1')ans2=(ans2+(int)num.at(j).toLatin1()-48)/2;
            else wrong="不合法的二进制数";
        }
    }

    return ans1+ans2;
}
double MainWindow::oct(QString expression,int l){//八进制转为十进制
    double ans1=0,ans2=0;
    int i=0;
    bool ok=true;
    QString num="";
    if(l>=expression.length()){
        wrong="表达式错误";
        return 0;
    }
    if(expression.at(l)=='-'){
        num.append('-');
        l++;
    }
    while(l<expression.length()&&(expression.at(l)>='0'&&expression.at(l)<='9'||expression.at(l)=='.')){
        num.append(expression.at(l));
        l++;
    }
    num.toDouble(&ok);
    nextpos=l;
    if(!ok)wrong="不合法的八进制数";
    else{
        for(;i<num.length()&&num.at(i)!='.';i++){
            if(num.at(i)>='0'&&num.at(i)<='7')ans1=ans1*8+(int)num.at(i).toLatin1()-48;
            else wrong="不合法的八进制数";
        }
        for(int j=num.length()-1;j>i;j--){
            if(num.at(j)>='0'&&num.at(j)<='7')ans2=(ans2+(int)num.at(j).toLatin1()-48)/8;
            else wrong="不合法的八进制数";
        }
    }

    return ans1+ans2;
}
double MainWindow::hex(QString expression,int l){//十六进制转为十进制
    double ans1=0,ans2=0;
    int i=0,f=0;
    bool ok=true;
    QString num="";
    if(l>=expression.length()){
        wrong="表达式错误";
        return 0;
    }
    if(expression.at(l)=='-'){
        num.append('-');
        l++;
    }
    while(l<expression.length()&&((expression.at(l)>='0'&&expression.at(l)<='9')||(expression.at(l)>='A'&&expression.at(l)<='F')||expression.at(l)=='.')){
        num.append(expression.at(l));
        if(expression.at(l)=='.')f++;
        l++;
    }
    if(f>1)ok=false;
    nextpos=l;
    if(!ok)wrong="不合法的十六进制数";
    else{
        for(;i<num.length()&&num.at(i)!='.';i++){
            if(num.at(i)>='0'&&num.at(i)<='9')ans1=ans1*16+(int)num.at(i).toLatin1()-48;
            else if(num.at(i)>='A'&&num.at(i)<='F')ans1=ans1*16+(int)num.at(i).toLatin1()-55;
            else wrong="不合法的十六进制数";
        }
        for(int j=num.length()-1;j>i;j--){
            if(num.at(j)>='0'&&num.at(j)<='9')ans1=(ans1+(int)num.at(j).toLatin1()-48)/16;
            else if(num.at(j)>='A'&&num.at(j)<='F')ans1=(ans1+(int)num.at(j).toLatin1()-55)/16;
            else wrong="不合法的十六进制数";
        }
    }

    return ans1+ans2;
}

int MainWindow::gcd(int a,int b){//求公约数
    if(b==0)return a;
    return gcd(b,a%b);
}

int MainWindow::lcm(int a,int b){//求公倍数
    return a*b/gcd(a,b);
}

double MainWindow::getnum(QString expression,int l)//将字符串转为数字
{
    double ans=0,pi=3.1415926535897;
    int len=expression.length();
    bool ok=true;//判断数字是否合法
    QString num="";
    if(l<len&&expression.at(l)=='('){//判断是否为括号，是括号则调用solve函数解决括号内的表达式
        ans=solve(expression,l+1,end[l]-1);
        nextpos=end[l]+1;
    }else if(l<len&&(expression.at(l)=='-'||(expression.at(l)>='0'&&expression.at(l)<='9'))){//判断是否为数字
        if(expression.at(l)=='-'){
            num.append('-');
            l++;
        }
        while((l<len)&&(expression.at(l)=='.'||(expression.at(l)>='0'&&expression.at(l)<='9'))){
            num.append(expression.at(l));
            l++;
        }
        ans=num.toDouble(&ok);
        if(!ok)wrong="表达式错误";
        nextpos=l;
    }else if(l<len&&(expression.at(l)>='a'&&expression.at(l)<='z')){//判断是否是单目运算符
        while(l<len&&expression.at(l)>='a'&&expression.at(l)<='z'){
            num.append(expression.at(l));
            l++;
        }
        if(QString::compare(num,"sin")==0){
            ans=sin(getnum(expression,l)/180*pi);
        }else if(QString::compare(num,"cos")==0){
            ans=cos(getnum(expression,l)/180*pi);
        }else if(QString::compare(num,"tan")==0){
            ans=tan(getnum(expression,l)/180*pi);
        }else if(QString::compare(num,"log")==0){
            ans=log10(getnum(expression,l));
        }else if(QString::compare(num,"ln")==0){
            ans=log(getnum(expression,l));
        }else if(QString::compare(num,"bin")==0){
            ans=bin(expression,l);
        }else if(QString::compare(num,"oct")==0){
            ans=oct(expression,l);
        }else if(QString::compare(num,"hex")==0){
            ans=hex(expression,l);
        }else{
            wrong="表达式错误";
        }
    }else{
        wrong="表达式错误";
    }
    return ans;
}
double MainWindow::solve(QString expression,int l,int r)
{
    double stack[10005][2];
    int len=0;
    stack[++len][0]=getnum(expression,l);//取数
    l=nextpos;                           //取完数后表达式左端变为数字结束坐标
    if(QString::compare(wrong,"")!=0)return 0;
    while(l<=r){
        if(expression.at(l)=='+'){
            stack[len][1]=0;
            stack[++len][0]=getnum(expression,l+1);
        }else if(expression.at(l)=='-'){
            stack[len][1]=1;
            stack[++len][0]=getnum(expression,l+1);
        }else if(expression.at(l)=='*'){
            stack[len][1]=2;
            stack[++len][0]=getnum(expression,l+1);
        }else if(expression.at(l)=='/'){
            stack[len][1]=3;
            stack[++len][0]=getnum(expression,l+1);
            if(stack[len][0]==0)wrong="除数不能为0";
        }else if(expression.at(l)=='^'){
            stack[len][1]=4;
            stack[++len][0]=getnum(expression,l+1);
        }else if(expression.at(l)=='g'){
            stack[len][1]=5;
            stack[++len][0]=solve(expression,l+3,r);
        }else if(expression.at(l)=='l'){
            stack[len][1]=6;
            stack[++len][0]=solve(expression,l+3,r);
        }else{
            wrong="表达式错误";
        }
        l=nextpos;
        if(QString::compare(wrong,"")!=0)return 0;
    }
    for(int i=len-1;i>=1;i--){
        if(stack[i][1]==4){
            stack[i][0]=pow(stack[i][0],stack[i+1][0]);
            stack[i][1]=2; stack[i+1][0]=1;
        }
    }
    for(int i=1;i<len;i++){
        if(stack[i][1]==2){
            stack[i+1][0]=stack[i][0]*stack[i+1][0];
            stack[i][1]=stack[i-1][1]; stack[i][0]=0;
        }else if(stack[i][1]==3){
            stack[i+1][0]=stack[i][0]/stack[i+1][0];
            stack[i][1]=stack[i-1][1]; stack[i][0]=0;
        }
    }
    for(int i=1;i<len;i++){
        if(stack[i][1]==0){
            stack[i+1][0]=stack[i][0]+stack[i+1][0];
        }else if(stack[i][1]==1){
            stack[i+1][0]=stack[i][0]-stack[i+1][0];
        }
    }
    if(stack[len-1][1]==5)return gcd((int)stack[len-1][0],(int)stack[len][0]);
    else if(stack[len-1][1]==6)return lcm((int)stack[len-1][0],(int)stack[len][0]);
    else return stack[len][0];
}
double MainWindow::calculation(QString expression)
{
    int len=0;
    for(int i=0;i<expression.length();i++){
        if(expression.at(i)=='('){
            queue[++len]=i;
        }else if(expression.at(i)==')'){
            end[queue[len]]=i; len--;
            if(len<0){
                wrong="括号不匹配";
                return 0;
            }
        }
    }
    if(len>0){
        wrong="括号不匹配";
        return 0;
    }
    else return solve(expression,0,expression.length()-1);
}
void MainWindow::startcalculate()
{
    wrong="";
    double result;
    QString ans;
    if(expression.length()==0)ans="";
    else {
        result=calculation(expression);
        ans=clearzero(QString::number(result,'f',10));
    }
    if(QString::compare(wrong,"")==0)ui->label2->setText(ans);
    else ui->label2->setText(wrong);
}

QString MainWindow::clearzero(QString ans)
{
    int i=0;
    for(;i<ans.length();i++){
        if(ans[i]=='.')break;
    }
    for(int j=ans.length()-1;j>=i;j--){
        if(ans[j]=='0'||ans[j]=='.')ans.chop(1);
        else break;
    }
    return ans;
}
void MainWindow::on_pushButton_1_clicked()
{
    expression.append('1');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_2_clicked()
{
    expression.append('2');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_3_clicked()
{
    expression.append('3');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_4_clicked()
{
    expression.append('4');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_5_clicked()
{
    expression.append('5');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_6_clicked()
{
    expression.append('6');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_7_clicked()
{
    expression.append('7');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_8_clicked()
{
    expression.append('8');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_9_clicked()
{
    expression.append('9');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_0_clicked()
{
    expression.append('0');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_div_clicked()
{
    expression.append('/');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_mul_clicked()
{
    expression.append('*');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_sub_clicked()
{
    expression.append('-');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_add_clicked()
{
    expression.append('+');
    ui->label->setText(expression);
}


void MainWindow::on_pushButton_point_clicked()
{
    expression.append('.');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_equal_clicked()
{

}

void MainWindow::on_pushButton_pow_clicked()
{
    expression.append('^');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_clr_clicked()
{
    expression="";
    ui->label->setText(expression);
    ui->label2->setText(expression);
}



void MainWindow::on_pushButton_mod_clicked()
{
    expression.append('%');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_pow1_clicked()
{
    expression.append("^(-1)");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_pow2_clicked()
{
    expression.append("^2");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_pow3_clicked()
{
    expression.append("^3");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_sin_clicked()
{
    expression.append("sin");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_cos_clicked()
{
    expression.append("cos");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_tan_clicked()
{
    expression.append("tan");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_log_clicked()
{
    expression.append("log");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_ln_clicked()
{
    expression.append("ln");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_left_clicked()
{
    expression.append('(');
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_right_clicked()
{
    expression.append(')');
    ui->label->setText(expression);
}


void MainWindow::on_pushButton_del_clicked()
{
    int i=expression.length()-1;
    if(i>=0){
        if(expression.at(i)>='a'&&expression.at(i)<='z'){
            while(i>=0&&expression.at(i)>='a'&&expression.at(i)<='z'){
                i--;
            }
            expression=expression.left(i+1);
        }else{
            expression=expression.left(i);
        }
    }
    ui->label->setText(expression);
    ui->label2->setText("");
}

void MainWindow::on_pushButton_bin_clicked()
{
    expression.append("bin");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_dec_clicked()
{
    expression.append("dec");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_oct_clicked()
{
    expression.append("oct");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_hex_clicked()
{
    expression.append("hex");
    ui->label->setText(expression);
}



void MainWindow::on_pushButton_A_clicked()
{
    expression.append("A");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_B_clicked()
{
    expression.append("B");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_C_clicked()
{
    expression.append("C");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_D_clicked()
{
    expression.append("D");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_E_clicked()
{
    expression.append("E");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_F_clicked()
{
    expression.append("F");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_gcd_clicked()
{
    expression.append("gcd");
    ui->label->setText(expression);
}

void MainWindow::on_pushButton_lcm_clicked()
{
    expression.append("lcm");
    ui->label->setText(expression);
}
