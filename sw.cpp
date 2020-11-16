/*#include <iostream>
#include <string>
using namespace std;
#include "protocol.h"

Packet *packet;
int Error = 0; //Error Flag

class StopAndWait
{
    public:
        string s;
        int length;
        int cursor;
        string r;
        StopAndWait(string s)
        {
            this->s = s;
            length = s.length();
            cursor = 0;
            r = "";
        }
        void sender();
        void reciever();
};

void StopAndWait :: sender()
{
    cout<<"SENDER\n";
    if(length <= 0)
    {
        to_physical_layer(reciever_frame);
        event = DONE;
        cout<<"\n";
        reciever();
        return;
    }
    while(length > 0)
    {
        if(event == frame_arrival)
        {
            if(sender_frame->seq == reciever_frame->ack)
            {
                to_physical_layer(reciever_frame);
                packet = new Packet();
                //creating the packet
                for(int i = 0; i < MAX_PKT; i++, cursor++)
                {
                    packet->d += s[cursor]; 
                }
                from_network_layer(packet);
                to_physical_layer(sender_frame);
                cout<<"\n";
            }
            else
            {
                cout<<"ACK Error\nResending....\n\n";
                Error = 0;
            }
        }
        else if(event == ESTB_CONN)
        {
            cout<<"Establishing Connection\n\n";
        }
        reciever();
    }

}

void StopAndWait :: reciever()
{
    cout<<"RECIEVER\n";
    if(event == frame_arrival)
    {
        if(!Error)
        {
            if(sender_frame->seq == reciever_sequence)
            {
                from_physical_layer(sender_frame);
                to_network_layer(packet);
                length -= MAX_PKT;
                r += packet->d;
                cout<<"\n";
                if(reciever_sequence%2 == 0)
                {
                    Error = 1;
                }
            }
        }
        else
        {
            from_physical_layer(sender_frame);
            cout<<"Decapsulating Recieved Frame\n";
            cout<<"Sending ACK \n\n";
        }
        
        sender();
    }
    else if(event == ESTB_CONN)
    {
        cout<<"Connection Estblished\n";
        event = frame_arrival;
        cout<<"\n";
        sender();
    }
    else if(event == DONE)
    {
        cout<<"Done\n";
        cout<<"\nDATA RECIEVED : "<<r; 
        return;
    }
}


int main()
{
    cout<<"     STOP AND WAIT PROTOCOL FOR NOISY CHANNEL\n";
    cout<<"(Every Frame with the Even Sequence Number has ACK Error)\n\n";
    cout<<"Enter the message to be sent : ";
    string s;
    getline(cin,s);
    StopAndWait *z = new StopAndWait(s);
    z->sender();
}*/










#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
using namespace std;
#define time 5
#define max_seq 1
#define tot_pack 5
int randn(int n)
{
    return rand()%n + 1;
}
typedef struct
{
       int data;
}packet;
typedef struct
{
        int kind;
        int seq;
        int ack;
        packet info;
}frame;
typedef enum{ frame_arrival,error,time_out}event_type;
frame data1;
//creating prototype
void from_network_layer(packet *);
void to_physical_layer(frame *);
void to_network_layer(packet *);
void from_physical_layer(frame*);
void sender();
void receiver();
void wait_for_event_sender(event_type *);
void wait_for_event_receiver(event_type *);
//end


#define inc(k) if(k<max_seq)k++;else k=0;


int i=1;
char turn;
int disc=0;
int main()
{
   while(!disc)
   {  sender();
     // delay(400);
      receiver();
   }
    getchar();
}
void sender()
{
     static int frame_to_send=0;
     static frame s;
     packet buffer;
     event_type event;
     static int flag=0;       //first place
     if (flag==0)
     {
   from_network_layer(&buffer);
   s.info=buffer;
   s.seq=frame_to_send;
   cout<<"\nsender information \t"<<s.info.data<<"\n";
   cout<<"\nsequence no. \t"<<s.seq;


   turn='r';
   to_physical_layer(&s);
   flag=1;
     }


 wait_for_event_sender(&event);
 if(turn=='s')
 {
     if(event==frame_arrival)
      {
      from_network_layer(&buffer);
      inc(frame_to_send);
      s.info=buffer;
      s.seq=frame_to_send;
      cout<<"\nsender information \t"<<s.info.data<<"\n";
      cout<<"\nsequence no. \t"<<s.seq<<"\n";


      getch();
      turn='r';
      to_physical_layer(&s);
      }


 }


}                   //end of sender function


void from_network_layer(packet *buffer)
{
     (*buffer).data=i;
     i++;
}                            //end of from network layer function


void to_physical_layer(frame *s)
{


     data1=*s;
}             //end of to physical layer function


void wait_for_event_sender(event_type *e)
{
      static int timer=0;
      if(turn=='s')
      {   timer++;
    //timer=0;
    return ;
  }


  else                          //event is frame arrival
    {
       timer=0;
       *e=frame_arrival;
    }


}              //end of wait for event function


void receiver()
{
     static int frame_expected=0;
     frame s,r;
     event_type event;
     wait_for_event_receiver(&event);
     if(turn=='r')
     {  if(event==frame_arrival)
    {
          from_physical_layer(&r);
          if(r.seq==frame_expected)
    {
       to_network_layer(&r.info);
       inc (frame_expected);
    }
    else
    cout<<"\nReceiver :Acknowledgement resent \n";
    getch();
    turn='s';
    to_physical_layer(&s);
      }


     }
}                     //end of receiver function




void wait_for_event_receiver(event_type *e)
{
     if(turn=='r')
     {
   *e=frame_arrival;
     }
}


void from_physical_layer(frame *buffer)
{
    *buffer=data1;
}


void to_network_layer(packet *buffer)
{
     cout<<"\nReceiver : packet received \t"<< i-1;
     cout<<"\n Acknowledgement  sent \t";
     getch();
     if(i>tot_pack)
      { disc=1;
 cout<<"\ndiscontinue\n";
      }
}        //end of network layer function