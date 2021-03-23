 #include <stdio.h>
 #include <stdlib.h>
 
 typedef struct Process 
 {
     int Process_num;
     int Arrive_time;
     int CPU_time;
  }
  Process;
  
 void Process_Sort(Process *Pro, int n) 
 {
    Process temp;
    int i, j;
     
    for(i = n-1; i > 0; i--) 
    {
       for(j = 0; j < i; j++) 
       {
          if(Pro[j].Arrive_time > Pro[j+1].Arrive_time) 
          {
             temp = Pro[j+1];
             Pro[j+1] = Pro[j];
             Pro[j] = temp;
          }
        else if(Pro[j].Arrive_time == Pro[j+1].Arrive_time && Pro[j].Process_num > Pro[j+1].Process_num) 
        {
          temp = Pro[j+1];
          Pro[j+1] = Pro[j];
          Pro[j] = temp;
         }
       }
     }
  }
 
  int Process_FCFS(Process *Pro, int n) 
  {
      int Waiting_Time = 0;
      int temp1, temp2;
      int i, j, k = 0;
 
      for(i = 1; i<n ; i++) 
      {
          temp1 = 0;
          for(j = k; j < i; j++) 
          {
              temp1 += Pro[j].CPU_time;
          }
          
          temp2 = temp1 - Pro[i].Arrive_time + Pro[k].Arrive_time;
          if(temp2 <= 0)
              k = i;
          else 
          {
              Waiting_Time += temp2;
          }
      }
     return Waiting_Time;
  }
 
  int main(void) 
  {
      int n, i;
      int result;
      Process *Ready_Queue;
      FILE *file = fopen("fcfs.inp", "rt");
      FILE *outfile = fopen("fcfs.out", "wt");
 
      fscanf(file, "%d\n", &n); //첫 줄 먹기
      Ready_Queue = (Process*)malloc(sizeof(Process)*n); //동적할당
 
      for(i = 0; i<n ; i++) 
      { 
        fscanf(file, "%d %d %d\n", &Ready_Queue[i].Process_num, &Ready_Queue[i].Arrive_time, &Ready_Queue[i].CPU_time);
        if(feof(file)!=0)
            break;
     }
      
      Process_Sort(Ready_Queue, n); //정렬
 
      /*for(int i=0; i<n; i++) {
          printf("%d %d %d \n", Ready_Queue[i].Process_num, Ready_Queue[i].Arrive_time, Ready_Queue[i].CPU_time);
      }*/
 
      result = Process_FCFS(Ready_Queue, n); //처리
      printf("%d \n", result);
 
      fprintf(outfile, "%d", result);
      fclose(file);
      fclose(outfile);
 
      return 0;
 }
