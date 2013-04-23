#include <iostream>
#include <stdio.h>


using namespace std;
////////////////////////////////////
struct Stack_int
{
    int info;
    Stack_int *next;
};
struct Stack_pt
{
    char* info;
    Stack_pt *next;
}
;
void info()
{
    cout<<"\033[1;32m  \033[1m\n"<<endl;
    cout<<"Brainf*ck to C++ (by Alexey Kovalevskiy)"<<endl;
    for (int i=0; i<111; ++i)
        cout<<'_';
    cout<<endl<<"Краткое описание синтаксиса языка:"<<endl<<"\"+\" - увеличить значение в текущей яйчейке на 1 "
        <<endl<<"\"-\" - уменьшить значение в текущей яйчейке на 1 "<<endl<<"\">\" - перейти к следующей яйчейке"
        <<endl<<"\"<\" - перейти к предыдущей яйчейке"<<endl<<"\",\" - ввод значения с клавиатуры в текущаю яйчейку"
        <<endl<<"\".\" - вывод значения из текущей яйчейки в консоль"<<endl<<"\"[\" - начинает цикл, текущая яйчейка назначается счётчиком"
        <<endl<<"\"]\" - заканчивает цикл, если счётчик = 0, и переходит к следующей итерации в противном случае"<<endl;
    for (int i=0; i<111; ++i)
        cout<<'_';
    cout<<endl<<"Введите команды. Для окончания ввода введите \"e\": ";
    cout<<"\033[1;32m\033[5m\n"<<">"<<"\033[1;32m\033[25m";
}
///////////////////////////////////////////////////////////////////////
void push_pt(Stack_pt *&pStack,char* info)
{
    Stack_pt *tmp = new Stack_pt;
    tmp->info=info;
    tmp->next=pStack;
    pStack=tmp;
}
void pop_pt(Stack_pt *&pStack)
{
    Stack_pt *tmp=pStack;
    pStack=pStack->next;
    delete tmp;
}
char* on_top_pt(Stack_pt *pStack)
{
    return pStack->info;
}
void push_int(Stack_int *&pStack,char info)
{
    Stack_int *tmp = new Stack_int;
    tmp->info=info;
    tmp->next=pStack;
    pStack=tmp;
}
void pop_int(Stack_int *&pStack)
{
    Stack_int *tmp=pStack;
    pStack=pStack->next;
    delete tmp;
}
int on_top_int(Stack_int *pStack)
{
    return pStack->info;
}
////////////////////////////////////////////////////////////////////////////////////////////
void cycle_begin(char *data,int counter,Stack_int *&counterStack,Stack_pt *&dataStack)
{
    push_int(counterStack,counter);
    push_pt(dataStack,data);

}
void cycle_end(char *data,int &counter,Stack_int *&counterStack,Stack_pt *&dataStack)
{
    if(*(on_top_pt(dataStack))==0)
    {
        pop_pt(dataStack);
        pop_int(counterStack);

    }
    else
    {
        counter=on_top_int(counterStack);
    }


}
void read_commands(char *code)
{


    char zuzu;
    while(true)
    {
        cin>>zuzu;
        if(zuzu=='e')
        {
            *code='e';
            code=NULL;
            break;
        }

        *code=zuzu;
        ++code;
    }
}
void execute(char code,char *&data, int &counter,Stack_pt *&dataStack,Stack_int *&counterStack)
{

    if(code=='+')
    {
        ++(*data);

    }

    else if(code=='-')
    {
        --(*data);

    }

    else if(code=='>')
    {
        ++data;

    }

    else if (code=='<')
    {
        --data;

    }

    else if (code=='.')
    {
        cout<<*data;

    }

    else if(code==',')
    {
        cin>>(*data);

    }
    else if(code=='[')
    {
        cycle_begin(data,counter,counterStack,dataStack);
    }
    else if(code==']')
    {
        cycle_end(data,counter,counterStack,dataStack);

    }
}
void new_memory(char*&data,char *code)
{
    int counter=0;
    int i=0;
    while(*(code+i)!='e')
    {
       if (*(code+i)=='>')
       ++counter;
       ++i;
    }
    data=new char [counter+1];
 

}

int main()
{

    char *data;
    char code[10000];
    char *ptc=code;
    int counter=0;
    Stack_pt *dataStack;
    Stack_int *counterStack;
    info();
    read_commands(ptc);
    new_memory(data,code);
    cout<<"Чтение завершено. Начинаю выполнение программы..."<<endl;
    while(code[counter]!='e')
    {
        execute(code[counter],data,counter,dataStack,counterStack);
        ++counter;
    }
    cout<<endl;
    return 0;
}

