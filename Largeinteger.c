#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define FILE_NAME "cal.txt"
#define FLOAT_NUMER_MAX_SIZE 32
#define NUMER_MAX_SIZE 100
#define INPUT_MAX_SIZE 100
#define LOG_SIZE 999999

#define _0and9compare(x) ('0' <= x && x <= '9')
#define aandecompare(x) (('a' <= x && x <= 'e') || ('A' <= x && x <= 'E'))
#define hcompare(x) (x == 'H' || x == 'h')
#define opercompare(x) (x == '+' || x == '-' || x == '*' || x == '/' || x == '%' || x == '=')
#define opernoequalcompare(x) (x == '+' || x == '-' || x == '*' || x == '/' || x == '%')
#define _123compare(x) (x == '1' || x == '2' || x == '3')
#define commandcompare(x) (x == 'L' || x == 'l' || x == 'R' || x == 'r' || x == 'T' || x == 't' || x == 'S' || x == 's' || x == 'Q' || x == 'q')

void varInit(char data[][NUMER_MAX_SIZE + 2], char a[], char b[], char c[], char d[], char e[], char h1[], char h2[], char h3[], int minus_checking[]);
void insertChar(char dst[], char src[], int minusabcde[], int dstIndex, int srcIndex); // src > dst,;
void selectH(char data[], char h1[], char h2[], char h3[], int minus_checking[], int index, int minusabcde[]);
void insertChar_abcdedata(char data[][NUMER_MAX_SIZE + 2], int minus_checking[], char a[], char b[], char c[], char d[], char e[], int number[], int minusabcde[]);
void insertChar_Hdata(char data[][NUMER_MAX_SIZE + 2], int minus_checking[], char h1[], char h2[], char h3[], int number[], int minusabcde[]);
void printLog(char log[], char a[], char b[], char c[], char d[], char e[], int minus_checking[]);
void insertLog(char log[], char data[], int strL);
int selectCommand(char data[][NUMER_MAX_SIZE + 2], char input[], int inputSize, char a[], char b[], char c[], char d[], char e[], char h1[], char h2[], char h3[], int minus_checking[], char log[], int minusabcde[]);
void pluckCharLeft(char input[], int inputSize, int pluckSize);
int strCompare(char str1[], char str2[], int str1Size, int str2Size); // return 1이면 앞이 더 큰거, retrun 0이면 뒤가 더 큰거
void numToHex(char input[], int inputSize, int minus, char log[]);
void shiftRight(int array[], int n, int maxSize);
void singlePrecision(char input[], int inputSize, int minus, char log[]);
void sharpToNum(char input[], int inputSize, char log[]);
void commaPrint(char input[], int minuscheck, char log[], int saveLog);
void zeroCharArray(char array[], int size);
void oneIntArray(int array[], int size);
void screen(char a[], char b[], char c[], char d[], char e[], int minus_checking[]);
void error(char log[]);
int spaceError(char input[], int inputSize);
int deleteSpaceAndCheck(char input[], int inputSize);
int operBetweenStr(char input[], int inputSize);
int charExist(char array[], char c);
int hashCommaStr(char input[], int inputSize);
int check(char input[], int inputSize);
int divideOperator(char input[100], char data[][NUMER_MAX_SIZE + 2], char index[], int minus_checking[], int number[], char log[]);
int f(int number, char data[][NUMER_MAX_SIZE + 2], char data_Index[], int minus_checking[], int number_cnt[], char a[], char b[], char c[], char d[], char e[], char log[], int minusabcde[]);
void remain(int front, int back, char data[][NUMER_MAX_SIZE + 2], int num_count[]);
int plus(int front, int back, char data[][NUMER_MAX_SIZE + 2]);
void multiply(int front, int back, char data[][NUMER_MAX_SIZE + 2]);
void minus(int front, int back, char data[][NUMER_MAX_SIZE + 2]);
int divide_minus(int front, int back, int start, int front_count, int back_count, char data[][NUMER_MAX_SIZE + 2]);
void divide(int front, int back, char data[][NUMER_MAX_SIZE + 2], int num_count[]);

int main()
{
       // 사용할 변수, 숫자 배열, minus_checking 배열 생성 및 초기화
       char a[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       char b[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       char c[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       char d[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       char e[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       static char h1[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       static char h2[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       static char h3[NUMER_MAX_SIZE + NUMER_MAX_SIZE];
       static char data[INPUT_MAX_SIZE][NUMER_MAX_SIZE + 2];

       int minus_checking[INPUT_MAX_SIZE] = {
           0,
       };

       int minusabcde[INPUT_MAX_SIZE] = {
           0,
       };

       char log[LOG_SIZE];

       varInit(data, a, b, c, d, e, h1, h2, h3, minus_checking);
       screen(a, b, c, d, e, minus_checking);

       char input[INPUT_MAX_SIZE];
       int inputSize;
       char inputTmp;
       int inputSpaceCount;
       int whileRange = 1;
       char strStdin[] = "(input) ";
       char strStdout[] = "======> ";
       char tmp[] = "\n";

       while (whileRange)
       {
              // input 배열 초기화
              zeroCharArray(input, NUMER_MAX_SIZE);

              // log 저장
              inputSize = 0;
              inputSpaceCount = 0;
              printf("%s", strStdin);
              insertLog(log, strStdin, strlen(strStdin));

              // oneline 입력받기
              while ((inputTmp = getchar()) != '\n')
              {
                     if (inputSize > INPUT_MAX_SIZE) // 100자리를 넘으면 입력무시
                     {
                            continue;
                     }

                     // 앞 공백 자르기
                     if (inputTmp == ' ' && inputSize == inputSpaceCount)
                     {
                            continue;
                     }
                     else if (inputTmp == ' ')
                     {
                            inputSpaceCount++;
                     }
                     input[inputSize] = inputTmp;
                     inputSize++;
              }

              // log 저장
              insertLog(log, input, strlen(input));
              insertLog(log, tmp, strlen(tmp));

              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));

              // input 배열 error 검사
              if (check(input, inputSize))
              {
                     error(log);
                     continue;
              }

              // 커맨드 선택
              if (selectCommand(data, input, inputSize, a, b, c, d, e, h1, h2, h3, minus_checking, log, minusabcde))
              {
                     whileRange = 0;
                     printf("bye\n");
                     continue;
              }
       }
}

void varInit(char data[][NUMER_MAX_SIZE + 2], char a[], char b[], char c[], char d[], char e[], char h1[], char h2[], char h3[], int minus_checking[])
{
       for (int i = 0; i < INPUT_MAX_SIZE; i++) // 숫자들이 파싱되어 있어가는 data 0으로 초기화
       {
              zeroCharArray(data[i], NUMER_MAX_SIZE + 2);
       }
       // data[51] ~ data[58] 은 a~e, h1~h3의 계산결과가 임시로 들어가는 위치, 때문에 0N으로 초기화
       data[51][0] = '0';
       data[51][1] = 'N';
       data[52][0] = '0';
       data[52][1] = 'N';
       data[53][0] = '0';
       data[53][1] = 'N';
       data[54][0] = '0';
       data[54][1] = 'N';
       data[55][0] = '0';
       data[55][1] = 'N';
       data[56][0] = '0';
       data[56][1] = 'N';
       data[57][0] = '0';
       data[57][1] = 'N';
       data[58][0] = '0';
       data[58][1] = 'N';
       // main에서 사용되는 a,b,c,d,e 변수들 0N으로 초기화
       zeroCharArray(a, INPUT_MAX_SIZE);
       zeroCharArray(b, INPUT_MAX_SIZE);
       zeroCharArray(c, INPUT_MAX_SIZE);
       zeroCharArray(d, INPUT_MAX_SIZE);
       zeroCharArray(e, INPUT_MAX_SIZE);
       zeroCharArray(h1, INPUT_MAX_SIZE);
       zeroCharArray(h2, INPUT_MAX_SIZE);
       zeroCharArray(h3, INPUT_MAX_SIZE);
       a[0] = '0';
       a[1] = 'N';
       b[0] = '0';
       b[1] = 'N';
       c[0] = '0';
       c[1] = 'N';
       d[0] = '0';
       d[1] = 'N';
       e[0] = '0';
       e[1] = 'N';
       h1[0] = '0';
       h1[1] = 'N';
       h2[0] = '0';
       h2[1] = 'N';
       h3[0] = '0';
       h3[1] = 'N';
       // -마이너스 따로 처리하는 minus_checking 변수 0으로 초기화
       for (int i = 0; i < INPUT_MAX_SIZE; i++)
       {
              minus_checking[i] = 0;
       }
}

void insertChar(char dst[], char src[], int minusabcde[], int dstIndex, int srcIndex) // src > dst,
{
       // src -> dst로 N까지 읽어서 복사, 이때 minus가 설정되어 있다면 minus까지 설정해주기
       int j;
       for (j = 0; src[j] != 'N'; j++)
              ;
       dst[j] = 'N';
       for (int i = 0; i < j; i++)
       {
              dst[i] = src[i];
       }
       if (minusabcde[srcIndex - 51])
       {
              minusabcde[dstIndex - 51] = 1;
       }
       else
       {
              minusabcde[dstIndex - 51] = 0;
       }
}

void selectH(char data[], char h1[], char h2[], char h3[], int minus_checking[], int index, int minusabcde[])
{
       int j;
       // h2 -> h3, h1 -> h2로 밀려야되기 때문에 insertChar로 밀어주기, 마이너스도 같이 설정해주기
       insertChar(h3, h2, minusabcde, 58, 57);
       insertChar(h2, h1, minusabcde, 57, 56);

       for (j = 0; data[j] != 'N'; j++)
       {
              h1[j] = data[j];
       }
       // minusabcde[5] == h1, 가장 최근이 h1이기 때문에
       h1[j] = 'N';
       if (minus_checking[index])
       {
              minusabcde[5] = 1;
       }
       else
       {
              minusabcde[5] = 0;
       }

       for (int k = 0; k < j; k++)
       {
              h1[k] = data[k];
       }
}

void insertChar_abcdedata(char data[][NUMER_MAX_SIZE + 2], int minus_checking[], char a[], char b[], char c[], char d[], char e[], int number[], int minusabcde[])
{
       int i;
       // minusabcde[0] == a, minusabcde[1] == b, minusabcde[0] == c.. 임 main변수 a,b,c,d,e를 data[51]~data[55]까지 마이너스를 포함하여 옮겨줌
       if (minusabcde[0])
       {
              for (i = 0; a[i] != 'N'; i++)
                     data[51][i] = a[i];
              data[51][i] = 'N';
              number[51] = i;
              minus_checking[51] = 1;
       }
       else
       {
              for (i = 0; a[i] != 'N'; i++)
                     data[51][i] = a[i];
              data[51][i] = 'N';
              number[51] = i;
              minus_checking[51] = 0;
       }
       if (minusabcde[1])
       {
              for (i = 0; b[i] != 'N'; i++)
                     data[52][i] = b[i];
              data[52][i] = 'N';
              number[52] = i;
              minus_checking[52] = 1;
       }
       else
       {
              for (i = 0; b[i] != 'N'; i++)
                     data[52][i] = b[i];
              data[52][i] = 'N';
              number[52] = i;
              minus_checking[52] = 0;
       }
       if (minusabcde[2])
       {
              for (i = 0; c[i] != 'N'; i++)
                     data[53][i] = c[i];
              data[53][i] = 'N';
              number[53] = i;
              minus_checking[53] = 1;
       }
       else
       {
              for (i = 0; c[i] != 'N'; i++)
                     data[53][i] = c[i];
              data[53][i] = 'N';
              number[53] = i;
              minus_checking[53] = 0;
       }
       if (minusabcde[3])
       {
              for (i = 0; d[i] != 'N'; i++)
                     data[54][i] = d[i];
              data[54][i] = 'N';
              number[54] = i;
              minus_checking[54] = 1;
       }
       else
       {
              for (i = 0; d[i] != 'N'; i++)
                     data[54][i] = d[i];
              data[54][i] = 'N';
              number[54] = i;
              minus_checking[54] = 0;
       }
       if (minusabcde[4])
       {
              for (i = 0; e[i] != 'N'; i++)
                     data[55][i] = e[i];
              data[55][i] = 'N';
              number[55] = i;
              minus_checking[55] = 1;
       }
       else
       {
              for (i = 0; e[i] != 'N'; i++)
                     data[55][i] = e[i];
              data[55][i] = 'N';
              number[55] = i;
              minus_checking[55] = 0;
       }
}

void insertChar_Hdata(char data[][NUMER_MAX_SIZE + 2], int minus_checking[], char h1[], char h2[], char h3[], int number[], int minusabcde[])
{
       int i;

       // minusabcde[5] == h1, minusabcde[6] == h2, minusabcde[7] == h3임 main변수 h1,h2,h3를 data[56]~data[58]까지 마이너스를 포함하여 옮겨줌
       if (minusabcde[5])
       {
              for (i = 0; h1[i] != 'N'; i++)
                     data[56][i] = h1[i];
              data[56][i] = 'N';
              number[56] = i;
              minus_checking[56] = 1;
       }
       else
       {
              for (i = 0; h1[i] != 'N'; i++)
                     data[56][i] = h1[i];
              data[56][i] = 'N';
              number[56] = i;
              minus_checking[56] = 0;
       }
       if (minusabcde[6])
       {
              for (i = 0; h2[i] != 'N'; i++)
                     data[57][i] = h2[i];
              data[57][i] = 'N';
              number[57] = i;
              minus_checking[57] = 1;
       }
       else
       {
              for (i = 0; h2[i] != 'N'; i++)
                     data[57][i] = h2[i];
              data[57][i] = 'N';
              number[57] = i;
              minus_checking[57] = 0;
       }
       if (minusabcde[7])
       {
              for (i = 0; h3[i] != 'N'; i++)
                     data[58][i] = h3[i];
              data[58][i] = 'N';
              number[58] = i;
              minus_checking[58] = 1;
       }
       else
       {
              for (i = 0; h3[i] != 'N'; i++)
                     data[58][i] = h3[i];
              data[58][i] = 'N';
              number[58] = i;
              minus_checking[58] = 0;
       }
}

void printLog(char log[], char a[], char b[], char c[], char d[], char e[], int minus_checking[])
{
       // 그동안 저장된 log를 출력하는 함수
       system("clear");
       // 변수들을 포함하는 screen함수를 같이 출력하게 함
       screen(a, b, c, d, e, minus_checking);
       printf("%s", log);
}

void insertLog(char log[], char data[], int strL)
{
       static int index;

       if (strL == -1)
       {
              zeroCharArray(log, index);
              index = 0;
              return;
       }
       for (int i = 0; i < strL; i++)
       {
              log[index + i] = data[i];
       }
       index += strL;
}

int selectCommand(char data[][NUMER_MAX_SIZE + 2], char input[], int inputSize, char a[], char b[], char c[], char d[], char e[], char h1[], char h2[], char h3[], int minus_checking[], char log[], int minusabcde[])
{
       // selectCommand의 return 값으로 q,Q 종료를 설정하였음
       FILE *fp;

       int number[59];
       char index[INPUT_MAX_SIZE + INPUT_MAX_SIZE];
       char strStdout[INPUT_MAX_SIZE];
       static int counton = 0;
       int errorNum = 0;

       int i, cnt, notPrint = 0, check;

       if (input[0] == 'Q' || input[0] == 'q')
       {
              return 1;
       }
       else if (input[0] == 'L' || input[0] == 'l') // L, l 커맨드
       {
              // cal.txt 파일을 읽어 fscanf로 값을 가져옴
              // a~e, h1~h3의 값들(N 포함, 마이너스 포함)이 저장됨
              fp = fopen(FILE_NAME, "r");
              if (fp == NULL)
              {
                     strcpy(strStdout, "파일이 존재하지 않습니다. 다시 시도해주세요.\n");
                     printf("%s", strStdout);
                     return 0;
              }
              // 문자열을 출력하고, log를 복사해둠
              strcpy(strStdout, "cal.txt로부터 복구\n");
              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));
              fscanf(fp, "%s", a);
              fscanf(fp, "%d", &minus_checking[51]);
              fscanf(fp, "%s", b);
              fscanf(fp, "%d", &minus_checking[52]);
              fscanf(fp, "%s", c);
              fscanf(fp, "%d", &minus_checking[53]);
              fscanf(fp, "%s", d);
              fscanf(fp, "%d", &minus_checking[54]);
              fscanf(fp, "%s", e);
              fscanf(fp, "%d", &minus_checking[55]);
              fscanf(fp, "%s", h1);
              fscanf(fp, "%d", &minus_checking[56]);
              fscanf(fp, "%s", h2);
              fscanf(fp, "%d", &minus_checking[57]);
              fscanf(fp, "%s", h3);
              fscanf(fp, "%d", &minus_checking[58]);
              fclose(fp);
              // 변수들 새로고침
              printLog(log, a, b, c, d, e, minus_checking);
       }
       else if (input[0] == 'R' || input[0] == 'r') // R, r 커맨드
       {
              // 화면 새로고침
              // 문자열을 출력하고, log를 복사해둠
              strcpy(strStdout, "\n");
              printf("%s", strStdout);
              insertLog(log, strStdout, -1);
              system("clear");
              screen(a, b, c, d, e, minus_checking);
       }
       else if (input[0] == 'T' || input[0] == 't') // T, t 커맨드
       {
              // 변수, 화면, h들 초기화
              // 문자열을 출력하고, log를 복사해둠
              strcpy(strStdout, "\n");
              printf("%s", strStdout);
              insertLog(log, strStdout, -1);
              system("clear");
              varInit(data, a, b, c, d, e, h1, h2, h3, minus_checking);
              screen(a, b, c, d, e, minus_checking);
       }
       else if (input[0] == 'S' || input[0] == 's') // S, s 커맨드
       {
              // a~e, h1~h3 변수들과 마이너스를 저장함
              // 문자열을 출력하고, log를 복사해둠
              fp = fopen(FILE_NAME, "w");
              strcpy(strStdout, "cal.txt에 저장\n");
              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));
              fprintf(fp, "%s\n%d\n", a, minus_checking[51]);
              fprintf(fp, "%s\n%d\n", b, minus_checking[52]);
              fprintf(fp, "%s\n%d\n", c, minus_checking[53]);
              fprintf(fp, "%s\n%d\n", d, minus_checking[54]);
              fprintf(fp, "%s\n%d\n", e, minus_checking[55]);
              fprintf(fp, "%s\n%d\n", h1, minus_checking[56]);
              fprintf(fp, "%s\n%d\n", h2, minus_checking[57]);
              fprintf(fp, "%s\n%d\n", h3, minus_checking[58]);
              fclose(fp);
       }
       else if ((input[0] == 'A' || input[0] == 'a') && input[1] == '\0') // a만 입력했을 떄
       {
              // a값 출력
              commaPrint(a, minus_checking[51], log, 1);
       }
       else if ((input[0] == 'B' || input[0] == 'b') && input[1] == '\0') // b만 입력했을 떄
       {
              // b값 출력
              commaPrint(b, minus_checking[52], log, 1);
       }
       else if ((input[0] == 'C' || input[0] == 'c') && input[1] == '\0') // c만 입력했을 떄
       {
              // c값 출력
              commaPrint(c, minus_checking[53], log, 1);
       }
       else if ((input[0] == 'D' || input[0] == 'd') && input[1] == '\0') // d만 입력했을 떄
       {
              // d값 출력
              commaPrint(d, minus_checking[54], log, 1);
       }
       else if ((input[0] == 'E' || input[0] == 'e') && input[1] == '\0') // e만 입력했을 떄
       {
              // e값 출력
              commaPrint(e, minus_checking[55], log, 1);
       }
       else if ((input[0] == 'H' || input[0] == 'h') && input[1] == '\0') // h 커맨드를 입력했을 떄
       {
              // h들의 값 출력
              strcpy(strStdout, "h1 = ");
              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));
              commaPrint(h1, minus_checking[56], log, 1);
              strcpy(strStdout, "======> h2 = ");
              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));
              commaPrint(h2, minus_checking[57], log, 1);
              strcpy(strStdout, "======> h3 = ");
              printf("%s", strStdout);
              insertLog(log, strStdout, strlen(strStdout));
              commaPrint(h3, minus_checking[58], log, 1);
       }
       else if ((input[0] == 'H' || input[0] == 'h') && input[1] == '1' && input[2] == '\0') // h1 커맨드를 입력했을 떄
       {
              commaPrint(h1, minus_checking[56], log, 1);
       }
       else if ((input[0] == 'H' || input[0] == 'h') && input[1] == '2' && input[2] == '\0') // h2 커맨드를 입력했을 떄
       {
              commaPrint(h2, minus_checking[57], log, 1);
       }
       else if ((input[0] == 'H' || input[0] == 'h') && input[1] == '3' && input[2] == '\0') // h3 커맨드를 입력했을 떄
       {
              commaPrint(h3, minus_checking[58], log, 1);
       }
       else if (input[0] == '#')
       {
              sharpToNum(input, inputSize, log); // # 커맨드를 입력했을 떄
       }
       else
       {      
              // 처음은 들어간 수가 없으므로 변수초기화 패스
              if (counton != 0)
                     insertChar_abcdedata(data, minus_checking, a, b, c, d, e, number, minusabcde);
              if (counton != 0)
                     insertChar_Hdata(data, minus_checking, h1, h2, h3, number, minusabcde);

              // 받은 값 인덱스로 정리
              cnt = divideOperator(input, data, index, minus_checking, number, log);

              // 오류 처리시 -1 반환되기에 한 파트 종료
              if (cnt == -1)
                     return 0;

              // 연산자 나눔 파트 진행
              check = f(cnt, data, index, minus_checking, number, a, b, c, d, e, log, minusabcde);

              // 오류 처리시 0 반환되기에 한 파트 종료
              if (check == 0)
                     return 0;

              // 계산된 index에 마지막으로 변수가 남아있는지, 인덱스가 남아있는지 확인하여, 정수 숫자로 바꿔주기
              // a=51,b=52..h1=56으로 설정됨
              for (int l = 0; l < strlen(index); l++)
              {
                     if ('a' <= index[l] && index[l] <= 'e')
                     {
                            i = index[l] - 'a' + 51;
                            break;
                     }
                     else if ((index[l] == 'h') && index[l + 1] == '1')
                     {
                            i = 56;
                            break;
                     }
                     else if ((index[l] == 'h') && index[l + 1] == '2')
                     {
                            i = 57;
                            break;
                     }
                     else if ((index[l] == 'h') && index[l + 1] == '3')
                     {
                            i = 58;
                            break;
                     }
                     else if (('0' <= index[l] && index[l] <= '9') && index[l + 1] == 'N')
                     {
                            i = index[l] - '0';
                            break;
                     }
                     else if (('0' <= index[l] && index[l] <= '9') && ('0' <= index[l + 1] && index[l + 1] <= '9') && index[l + 2] == 'N')
                     {
                            i = (index[l] - '0') * 10 + (index[l + 1] - '0');
                            break;
                     }
              }

              for (errorNum = 0; data[i][errorNum] != 'N'; errorNum++)
                     ;

              // 30글자가 넘으면 에러
              if (errorNum > 30)
              {
                     error(log);
                     return 0;
              }

              // 3글자씩 , 으로 나눠서 출력, log에 저장
              commaPrint(data[i], minus_checking[i], log, 1);

              // H 밀기 h1->h2, h2->h3
              selectH(data[i], h1, h2, h3, minus_checking, i, minusabcde);
              insertChar_abcdedata(data, minus_checking, a, b, c, d, e, number, minusabcde);
              insertChar_Hdata(data, minus_checking, h1, h2, h3, number, minusabcde);
              counton++;
              // = 대입연산자라면 저장된 log 출력
              if (index[1] == '=')
              {
                     printLog(log, a, b, c, d, e, minus_checking);
              }
              // index 배열 초기화
              zeroCharArray(index, INPUT_MAX_SIZE);
       }
       return 0;
}

void pluckCharLeft(char input[], int inputSize, int pluckSize)
{
       // 문자열 배열을 pluckSize 값 만큼 왼쪽으로 밀기
       int i;
       for (i = 0; i < inputSize - pluckSize; i++)
       {
              input[i] = input[i + pluckSize];
       }
       input[i] = '\0';
}

int strCompare(char str1[], char str2[], int str1Size, int str2Size) // return 1이면 앞이 더 큰거, retrun 0이면 뒤가 더 큰거
{
       // str1과 str2를 비교하여 더 큰값을 찾아줌
       int str1N, str2N;
       if (str1Size > str2Size)
       {
              return 1;
       }
       else if (str1Size < str2Size)
       {
              return 0;
       }
       else if (str1Size == str2Size)
       {
              for (int i = 0; i < str1Size; i++)
              {
                     str1N = str1[i] - '0';
                     str2N = str2[i] - '0';
                     if (str1N > str2N)
                     {
                            return 1;
                     }
                     else if (str1N < str2N)
                     {
                            return 0;
                     }
              }
       }
       return 1;
}

void numToHex(char input[], int inputSize, int minus, char log[])
{
       // # 커맨드로 입력받은 숫자가 정수형 일 경우
       char strStdin[] = "0x";
       char strStdout[] = "\n";
       char compareStr[] = "2147483648";
       if (minus)
       {
              compareStr[9] = '9';
       }
       // 마이너스면 -2147483649보다 큰지, 아니면 2147483648보다 큰지 확인, int 범위인지 확인
       if (strCompare(input, compareStr, inputSize, 10))
       {
              error(log);
              return;
       }

       int copyArray[FLOAT_NUMER_MAX_SIZE] = {
           0,
       };
       int sum = 0;
       int mulN;
       // 문자열 숫자를 정수형 숫자로 변환
       for (int i = 0; i < inputSize; i++)
       {
              mulN = 1;
              for (int j = 0; j < inputSize - i - 1; j++)
              {
                     mulN *= 10;
              }
              sum += (input[i] - '0') * mulN;
       }

       // 이진수로 변환
       int index = 0;
       while (sum > 0)
       {
              copyArray[index] = sum % 2;
              sum = sum / 2;
              index++;
       }
       // 만약 마이너스라면 2의 보수로 변환
       if (minus)
       {
              for (int i = 0; i < FLOAT_NUMER_MAX_SIZE; i++)
              {
                     copyArray[i] = !copyArray[i];
              }
              copyArray[0] += 1;
              for (int i = 0; i < FLOAT_NUMER_MAX_SIZE; i++)
              {
                     if (copyArray[i] > 1)
                     {
                            copyArray[i] -= 2;
                            copyArray[i + 1] += 1;
                     }
              }
              index = 32;
       }
       // 4글자씩 가져와 16진수로 변환
       char result[9];
       zeroCharArray(result, 9);
       int binary;
       int binaryIndex = 0;
       for (int i = 0; i < index; i += 4)
       {
              binary = copyArray[i] + copyArray[i + 1] * 2 + copyArray[i + 2] * 4 + copyArray[i + 3] * 8;
              if (binary >= 10)
              {
                     result[binaryIndex] = binary - 10 + 'A';
              }
              else
              {
                     result[binaryIndex] = binary + '0';
              }
              binaryIndex++;
       }

       char printArray[binaryIndex];
       zeroCharArray(printArray, binaryIndex);
       // 거꾸로 된 배열을 제대로 변환
       for (int i = 0; i < binaryIndex; i++)
       {
              printArray[i] = result[binaryIndex - 1 - i];
       }
       // 배열을 출력하고, log에 저장
       printf("%s", strStdin);
       insertLog(log, strStdin, strlen(strStdin));
       for (int i = 0; i < binaryIndex; i++)
       {
              printf("%c", printArray[i]);
       }
       insertLog(log, printArray, binaryIndex);
       printf("%s", strStdout);
       insertLog(log, strStdout, strlen(strStdout));
}

void shiftRight(int array[], int n, int maxSize)
{
       // 배열이 정수형일 때 오른쪽으로 밀기
       for (int i = n; i < maxSize; i++)
       {
              array[i] = array[i - n];
              array[i - n] = 0;
       }
}

void singlePrecision(char input[], int inputSize, int minus, char log[])
{
       // # 커맨드의 실수형 문자가 들어왔을 때
       char strStdin[] = "0x";
       char strStdout[] = "\n";
       int integerSize;
       // .을 기준으로 정수부분, 실수부분 인덱스 얻기
       for (integerSize = 0; input[integerSize] != '.'; integerSize++)
              ;
       int decimalSize = inputSize - integerSize - 1;

       int singerPart[23] = {
           0,
       };
       int sumI = 0, sumICopy;
       int mulN;
       // 정수부분 문자를 숫자로 바꾸기
       for (int i = 0; i < integerSize; i++)
       {
              mulN = 1;
              for (int j = 0; j < integerSize - i - 1; j++)
              {
                     mulN *= 10;
              }
              sumI += (input[i] - '0') * mulN;
       }

       sumICopy = sumI;
       int index = 0;
       while (sumI > 0) // 정수부분 이진수 변환
       {
              singerPart[index] = sumI % 2;
              sumI = sumI / 2;
              index++;
       }

       // 실수문자 부분 실수로 변환
       float sumF = 0, sumFCopy;
       float mulNF;
       for (int i = 0; i < decimalSize; i++)
       {
              mulNF = 1;
              for (int j = 0; j < i + 1; j++)
              {
                     mulNF *= 0.1;
              }
              sumF += (input[i + integerSize + 1] - '0') * mulNF;
       }

       // 실수를 이진수로 변환
       int exponentDefaultIndex = index;
       sumFCopy = sumF;
       int exponentTmpIndex = 0;
       if (sumICopy == 0)
       {
              while (sumFCopy < 1)
              {
                     sumFCopy = sumFCopy * 2;
                     exponentTmpIndex++;
              }
              exponentDefaultIndex = -(exponentTmpIndex - 1);
              exponentTmpIndex--;
       }

       // 정수부분과 소수부분 이진수를 합쳐서 23비트로 바꿔줌
       for (int i = 23 - index; i >= 0; i--)
       {
              sumF = sumF * 2;
              singerPart[i + exponentTmpIndex] = (int)sumF;

              if (sumF >= 1)
              {
                     sumF -= 1;
              }
              if (i == 0 && sumF >= 0.5)
              {
                     singerPart[i + exponentTmpIndex] += 1;
              }
       }

       int exponentPart[8] = {
           0,
       };
       int exponentDefault = 127 + (exponentDefaultIndex - 1);
       int exponentIndex = 0;
       int exponentRemain;
       // 지수부분 처리
       while (exponentDefault > 0)
       {
              exponentRemain = exponentDefault % 2;
              exponentPart[exponentIndex] = exponentRemain;
              exponentDefault = exponentDefault / 2;
              exponentIndex++;
       }

       char final[32] = {
           0,
       }; // 부호부분
       final[0] = minus;

       // 지수부분
       for (int i = 1; i <= 8; i++)
       {
              final[i] = exponentPart[8 - i];
       }

       // 소수부분
       for (int i = 9; i < 32; i++)
       {
              final[i] = singerPart[31 - i];
       }

       // 16진수로 변환
       char result[9];
       zeroCharArray(result, 9);
       int binary;
       int binaryIndex = 0;
       for (int i = 0; i < 32; i += 4)
       {
              binary = final[i] * 8 + final[i + 1] * 4 + final[i + 2] * 2 + final[i + 3] * 1;
              if (binary >= 10)
              {
                     result[binaryIndex] = binary - 10 + 'A';
              }
              else
              {
                     result[binaryIndex] = binary + '0';
              }
              binaryIndex++;
       }

       // 출력후 log 저장
       printf("%s", strStdin);
       insertLog(log, strStdin, strlen(strStdin));
       for (int i = 0; i < binaryIndex; i++)
       {
              printf("%c", result[i]);
       }
       insertLog(log, result, binaryIndex);
       printf("%s", strStdout);
       insertLog(log, strStdout, strlen(strStdout));
}

void sharpToNum(char input[], int inputSize, char log[])
{
       // #붙어있는 문자열을 잘라줌
       int pluckSize = 1;
       pluckCharLeft(input, inputSize, pluckSize);
       inputSize -= pluckSize;

       // 마이너스 소수, 플러스 소수, 마이너스 정수, 플러스 정수 나누기
       if (charExist(input, '.'))
       {
              if (input[0] == '-')
              {
                     pluckCharLeft(input, inputSize, pluckSize);
                     inputSize -= pluckSize;
                     singlePrecision(input, inputSize, 1, log);
              }
              else
              {
                     singlePrecision(input, inputSize, 0, log);
              }
       }
       else
       {
              if (input[0] == '-')
              {
                     pluckCharLeft(input, inputSize, pluckSize);
                     inputSize -= pluckSize;
                     numToHex(input, inputSize, 1, log);
              }
              else
              {
                     numToHex(input, inputSize, 0, log);
              }
       }
}

void commaPrint(char input[], int minuscheck, char log[], int saveLog)
{
       // 입력받은 문자열을 ,로 3개씩 나눠서 출력
       char strStdout[] = "\n";
       char strMinus[] = "-";
       int inputSize;

       // 마이너스라면 -출력, log 저장
       if (minuscheck == 1)
       {
              printf("%s", strMinus);
              if (saveLog)
              {
                     insertLog(log, strMinus, strlen(strMinus));
              }
       }

       for (inputSize = 0; input[inputSize] != 'N'; inputSize++)
              ;

       // 3글자씩 잘랐을 때 증가되는 인덱스 계산
       int cnt = 0;
       for (int i = 0; i < inputSize + cnt; i++)
       {
              if ((i + 1) % 4 == 0)
              {
                     cnt++;
              }
       }
       char printArray[inputSize + cnt];
       zeroCharArray(printArray, inputSize + cnt);

       // 계산된 인덱스로 , 넣기
       cnt = 0;
       for (int i = 0; i < inputSize + cnt; i++)
       {
              if ((i + 1) % 4 == 0)
              {
                     printArray[i] = ',';
                     cnt++;
              }
              else
              {
                     printArray[i] = input[i - cnt];
              }
       }

       // 거꾸로 된 배열 제대로 돌리기
       char insertArray[inputSize + cnt];
       zeroCharArray(insertArray, inputSize + cnt);
       for (int i = 0; i < inputSize + cnt; i++)
       {
              insertArray[i] = printArray[inputSize + cnt - 1 - i];
       }

       // 문자열 출력, log 저장, saveLog로 log를 저장할지 안할지 나눌 수 있음
       for (int i = 0; i < inputSize + cnt; i++)
       {
              printf("%c", insertArray[i]);
       }
       if (saveLog)
              insertLog(log, insertArray, inputSize + cnt);
       printf("%s", strStdout);
       if (saveLog)
              insertLog(log, strStdout, strlen(strStdout));
}

void zeroCharArray(char array[], int size)
{
       // char 배열 0으로 초기화
       for (int i = 0; i < size; i++)
       {
              array[i] = 0;
       }
}

void oneIntArray(int array[], int size)
{
       // int 배열 1로 초기화
       for (int i = 0; i < size; i++)
       {
              array[i] = 1;
       }
}

void screen(char a[], char b[], char c[], char d[], char e[], int minus_checking[])
{
       // 프로그램 메인화면
       int i;
       printf("*********************************************************************"
              "***\n");
       printf("                            큰 정수 계산기                           "
              "    \n");
       printf("*********************************************************************"
              "***\n");
       printf("변 수                                                                "
              "    \n");
       printf("*********************************************************************"
              "***\n");
       printf("a = ");
       commaPrint(a, minus_checking[51], 0, 0);
       printf("b = ");
       commaPrint(b, minus_checking[52], 0, 0);
       printf("c = ");
       commaPrint(c, minus_checking[53], 0, 0);
       printf("d = ");
       commaPrint(d, minus_checking[54], 0, 0);
       printf("e = ");
       commaPrint(e, minus_checking[55], 0, 0);
       printf("*********************************************************************"
              "***\n");
       printf("Help : H(istory) L(oad) R(eflesh) (rese)T S(ave) Q(uit)              "
              "   \n");
       printf("*********************************************************************"
              "***\n");
}

void error(char log[])
{
       // error를 출력하고 log 저장
       char strStdout[] = "error\n";
       printf("%s", strStdout);
       insertLog(log, strStdout, strlen(strStdout));
}

int spaceError(char input[], int inputSize)
{
       // 공백이 있을 때 발생할 수 있는 오류 처리
       for (int i = 0; i < inputSize; i++)
       {
              if (hcompare(input[i - 3]) && _123compare(input[i - 2]) && input[i - 1] == ' ' && !opercompare(input[i])) // h1~h3 이후 연산자가 아닐 경우 // h1 9
              {
                     return 1;
              }
              else if (_0and9compare(input[i - 2]) && input[i - 1] == ' ' && !opercompare(input[i])) // 숫자 이후 연산자가 아닐경우 // 123 2
              {
                     return 1;
              }
              else if (aandecompare(input[i - 2]) && input[i - 1] == ' ' && !opercompare(input[i])) // 변수 이후 연산자가 아닐경우 // a 1
              {
                     return 1;
              }
              else if (opercompare(input[i - 3]) && input[i - 2] == ' ' && input[i - 1] == '-' && input[i] == ' ') // 연산자 이후 마이너스 공백인 경우 // +(공백)-(공백)
              {
                     return 1;
              }
              else if (opercompare(input[i - 2]) && input[i - 1] == '-' && input[i] == ' ') // 연산자 이후 마이너스 공백인 경우 // +-(공백)
              {
                     return 1;
              }
              else if (i == 0 && input[i] == '-' && input[i + 1] == ' ' && _0and9compare(input[i + 2])) // 공백이 있는 음수인경우 // - 123
              {
                     return 1;
              }
       }
       return 0;
}

int deleteSpaceAndCheck(char input[], int inputSize)
{
       // 공백 제거
       // 문자열 길이 return
       int cnt = 0;
       for (int i = 0; i < inputSize; i++)
       {
              if (input[i] != ' ')
              {
                     input[cnt++] = input[i];
              }
       }
       input[cnt] = '\0';
       return strlen(input);
}

int operBetweenStr(char input[], int inputSize)
{
       // 1로 차있는 배열을 만들어 두고, 가능한 경우만 0으로 변경, whitebox 필터링
       int checkArray[inputSize];
       oneIntArray(checkArray, inputSize);
       int i;
       for (i = 0; i < inputSize; i++)
       {
              if ((hcompare(input[i - 2]) && _123compare(input[i - 1])) && opernoequalcompare(input[i]) && _0and9compare(input[i + 1])) // h1+숫자
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if ((hcompare(input[i - 2]) && _123compare(input[i - 1])) && opernoequalcompare(input[i]) && input[i + 1] == '-' && _0and9compare(input[i + 2])) // h1+음수숫자
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if ((hcompare(input[i - 2]) && _123compare(input[i - 1])) && opernoequalcompare(input[i]) && aandecompare(input[i + 1])) // h1+(변수)
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if ((hcompare(input[i - 2]) && _123compare(input[i - 1])) && opernoequalcompare(input[i]) && (hcompare(input[i + 1]) && _123compare(input[i + 2]))) // h1+h1
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (_0and9compare(input[i - 1]) && opernoequalcompare(input[i]) && _0and9compare(input[i + 1])) // 숫자+숫자
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (_0and9compare(input[i - 1]) && opernoequalcompare(input[i]) && input[i + 1] == '-' && _0and9compare(input[i + 2])) // 숫자+음수숫자
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (_0and9compare(input[i - 1]) && opernoequalcompare(input[i]) && aandecompare(input[i + 1])) // 숫자+(변수)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (_0and9compare(input[i - 1]) && opernoequalcompare(input[i]) && (hcompare(input[i + 1]) && _123compare(input[i + 2]))) // 숫자+h1
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (input[i - 2] == '-' && _0and9compare(input[i - 1]) && opernoequalcompare(input[i]) && _0and9compare(input[i + 1])) // 음수숫자+숫자
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if ((input[i - 2] == '-' && _0and9compare(input[i - 1])) && opernoequalcompare(input[i]) && (input[i + 1] == '-' && _0and9compare(input[i + 2]))) // 음수숫자+음수숫자
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if ((input[i - 2] == '-' && _0and9compare(input[i - 1])) && opernoequalcompare(input[i]) && aandecompare(input[i + 1])) // 음수숫자+(변수)
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if ((input[i - 2] == '-' && _0and9compare(input[i - 1])) && opernoequalcompare(input[i]) && (hcompare(input[i + 1]) && _123compare(input[i + 2]))) // 음수숫자+h1
              {
                     checkArray[i - 2] = 0;
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (aandecompare(input[i - 1]) && opernoequalcompare(input[i]) && _0and9compare(input[i + 1])) // (변수)+숫자
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (aandecompare(input[i - 1]) && opernoequalcompare(input[i]) && input[i + 1] == '-' && _0and9compare(input[i + 2])) // (변수)+음수숫자
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (aandecompare(input[i - 1]) && opernoequalcompare(input[i]) && (hcompare(input[i + 1]) && _123compare(input[i + 2]))) // (변수)+h1
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (aandecompare(input[i - 1]) && opernoequalcompare(input[i]) && aandecompare(input[i + 1])) // (변수)+(변수)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (aandecompare(input[i - 1]) && input[i] == '=' && _0and9compare(input[i + 1]) && i == 1) // (변수)=(숫자)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (aandecompare(input[i - 1]) && input[i] == '=' && input[i + 1] == '-' && _0and9compare(input[i + 2]) && i == 1) // (변수)=-(숫자)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (aandecompare(input[i - 1]) && input[i] == '=' && aandecompare(input[i + 1]) && opernoequalcompare(input[i + 2]) && i == 1) // (변수)=(변수)(연산자)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (aandecompare(input[i - 1]) && input[i] == '=' && aandecompare(input[i + 1]) && input[i + 2] == '\0' && i == 1) // (변수)=(변수)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }

              else if (aandecompare(input[i - 1]) && input[i] == '=' && (hcompare(input[i + 1]) && _123compare(input[i + 2])) && i == 1) // (변수)=(h1)
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     checkArray[i + 2] = 0;
                     i += 2;
              }
              else if (i == 0 && (commandcompare(input[i]) || hcompare(input[i])) && input[i + 1] == '\0') // l, s .. 커맨드
              {
                     checkArray[i] = 0;
              }
              else if (i == 0 && (hcompare(input[i]) && _123compare(input[i + 1])) && input[i + 2] == '\0') // h1 커맨드
              {
                     checkArray[i] = 0;
                     checkArray[i + 1] = 0;
                     i++;
              }
              else if (i == 0 && aandecompare(input[i]) && input[i + 1] == '\0') // 변수 커맨드
              {
                     checkArray[i] = 0;
              }
              else if (input[i - 1] == '-' && _0and9compare(input[i])) // -숫자
              {
                     checkArray[i - 1] = 0;
                     checkArray[i] = 0;
              }
              else if (_0and9compare(input[i]) || input[i] == '#' || input[i] == '.') // 숫자, #, .
              {
                     checkArray[i] = 0;
              }
       }

       // 다 더해서 0만 허용
       int sum = 0;
       for (int j = 0; j < inputSize; j++)
       {
              sum += checkArray[j];
       }
       return sum != 0;
}

int charExist(char array[], char c)
{
       // char 배열에서 문자열 c 1개만 존재 확인
       int cnt = 0;
       for (int i = 0; i < strlen(array); i++)
       {
              if (array[i] == c)
                     cnt++;
       }
       if (cnt == 1)
              return 1;
       return 0;
}

int hashCommaStr(char input[], int inputSize)
{
       // #이 있을 때 발생할 수 있는 오류처리
       int i;
       if (input[0] != '#' && charExist(input, '.')) // #이 없지만. 이 존재
       {
              return 1;
       }
       else if (input[0] == '#' && input[1] == '.') // #.123
       {
              return 1;
       }
       else if (input[0] == '#' && input[inputSize - 1] == '.') // #132123.
       {
              return 1;
       }
       else if (input[0] == '#' && input[1] == '-' && input[2] == '.') // #-.123
       {
              return 1;
       }
       if (input[0] == '#') // #이후에 숫자가 아니거나 . 이 아니면 오류
       {
              if (input[1] == '-')
              {
                     i = 2;
              }
              else if (input[1] == '\0')
              {
                     return 1;
              }
              else
              {
                     i = 1;
              }
              for (; i < inputSize; i++)
              {
                     if (input[i] != '.' && !_0and9compare(input[i]))
                     {
                            return 1;
                     }
              }
       }

       return 0;
}

int check(char input[], int inputSize)
{
       // 모든 오류처리
       if (inputSize > INPUT_MAX_SIZE || inputSize <= 0) // inputsize가 100을 넘을 때, 0보다 작을떄
       {
              return 1;
       }

       if (hashCommaStr(input, inputSize)) // # 있을 때 오류
       {
              return 1;
       }

       if (spaceError(input, inputSize)) // 공백이 있을 때 오류
       {
              return 1;
       }

       inputSize = deleteSpaceAndCheck(input, inputSize); // 공백제거

       if (operBetweenStr(input, inputSize)) // 모든 오류
       {
              return 1;
       }
       return 0;
}

int divideOperator(char input[100], char data[][NUMER_MAX_SIZE + 2], char index[], int minus_checking[], int number[], char log[])
{
       int i, tmp;
       int location = 0, number_cnt = 0, data_number = 0, minus_check = 0;
       // 인덱스 배열의 삽입 위치, 인덱스의 갯수, 숫자의 길이, 단항 연산 확인

       for (i = 0; i < strlen(input); i++)
       {
              // 연산자 발견시 연산자 앞의 수 인덱스 정리
              if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/' || input[i] == '%' || input[i] == '=')
              {
                     // 단항 연산자 포함인지 확인
                     if (input[i] == '-' && (i == 0 || input[i - 1] == '+' || input[i - 1] == '-' || input[i - 1] == '*' || input[i - 1] == '/' || input[i - 1] == '%' || input[i - 1] == '='))
                     {
                            minus_check = 1;
                     }
                     else
                     {

                            // 수가 h1~h3일 때
                            if (input[i - 2] == 'h' || input[i - 2] == 'H')
                            {

                                   // h의 숫자 data 배열로 삽입
                                   for (int f = 0; data[7 + input[i - 1]][f] != 'N'; f++)
                                   {
                                          data[number_cnt][f] = data[input[i - 1] + 7][f];
                                          data[number_cnt][f + 1] = 'N';
                                          number[number_cnt] = f + 1;
                                   }

                                   // 음수인지 확인
                                   if (minus_checking[input[i - 1] + 7] == 1)
                                          minus_checking[number_cnt] = 1;

                                   // 인덱스 표기
                                   if (number_cnt > 9)
                                   {
                                          index[location] = number_cnt / 10 + '0';
                                          location++;
                                          index[location] = number_cnt % 10 + '0';
                                          location++;
                                   }
                                   else
                                   {
                                          index[location] = number_cnt + '0';
                                          location++;
                                   }
                                   number_cnt++;

                                   // 연산자도 인덱스 배열에 삽입
                                   index[location] = input[i];
                                   location++;
                            }
                            else if ('a' <= input[i - 1] && input[i - 1] <= 'e')
                            {
                                   // 만약 변수 삽입이라면 인덱스 배열에 문자 그대로 삽입
                                   if (input[i] == '=')
                                   {
                                          index[location] = input[i - 1];
                                          location++;

                                          index[location] = input[i];
                                          location++;
                                   }
                                   else
                                   {
                                          // a~e의 숫자 data 배열로 삽입
                                          for (int f = 0; data[input[i - 1] - 'a' + 51][f] != 'N'; f++)
                                          {
                                                 data[number_cnt][f] = data[input[i - 1] - 'a' + 51][f];
                                                 data[number_cnt][f + 1] = 'N';
                                                 number[number_cnt] = f + 1;
                                          }

                                          // 음수인지 확인
                                          if (minus_checking[input[i - 1] - 'a' + 51] == 1)
                                          {
                                                 minus_checking[number_cnt] = 1;
                                          }
                                          else
                                          {
                                                 minus_checking[number_cnt] = 0;
                                          }

                                          // 인덱스 표기
                                          if (number_cnt > 9)
                                          {
                                                 index[location] = number_cnt / 10 + '0';
                                                 location++;
                                                 index[location] = number_cnt % 10 + '0';
                                                 location++;
                                          }
                                          else
                                          {
                                                 index[location] = number_cnt + '0';
                                                 location++;
                                          }
                                          number_cnt++;

                                          // 연산자도 인덱스 배열로 삽입
                                          index[location] = input[i];
                                          location++;
                                   }
                            }
                            else if ('A' <= input[i - 1] && input[i - 1] <= 'E') //소문자와 동일
                            {
                                   if (input[i] == '=')
                                   {
                                          index[location] = input[i - 1] + 32;
                                          location++;

                                          index[location] = input[i];
                                          location++;
                                   }
                                   else
                                   {
                                          for (int f = 0; data[input[i - 1] - 'A' + 51][f] != 'N'; f++)
                                          {
                                                 data[number_cnt][f] = data[input[i - 1] - 'A' + 51][f];
                                                 data[number_cnt][f + 1] = 'N';
                                                 number[number_cnt] = f + 1;
                                          }
                                          if (minus_checking[input[i - 1] - 'A' + 51] == 1)
                                          {
                                                 minus_checking[number_cnt] = 1;
                                          }
                                          else
                                          {
                                                 minus_checking[number_cnt] = 0;
                                          }

                                          if (number_cnt > 9)
                                          {
                                                 index[location] = number_cnt / 10 + '0';
                                                 location++;
                                                 index[location] = number_cnt % 10 + '0';
                                                 location++;
                                          }
                                          else
                                          {
                                                 index[location] = number_cnt + '0';
                                                 location++;
                                          }
                                          number_cnt++;

                                          index[location] = input[i];
                                          location++;
                                   }
                            }
                            else
                            {
                                   // 앞쪽의 수 확인하여 reverse로 data 배열에 삽입
                                   data_number = 0;
                                   for (int f = i - 1; '0' <= input[f] && input[f] <= '9'; f--)
                                   {
                                          if (data_number > 29)
                                          {
                                                 error(log);
                                                 return -1;
                                          }
                                          data[number_cnt][data_number] = input[f];
                                          data_number++;
                                   }

                                   // 수 앞쪽에 0이 있다면 지워주기
                                   data_number--;
                                   if (data[number_cnt][data_number] == '0' && data_number != 0)
                                   {
                                          while (data[number_cnt][data_number] == '0' && data_number != 0)
                                          {
                                                 data[number_cnt][data_number] = 'N';
                                                 data_number--;
                                          }
                                   }
                                   data_number++;

                                   // 숫자의 길이 number 배열 삽입
                                   number[number_cnt] = data_number;
                                   data[number_cnt][data_number] = 'N';

                                   // 인덱스 표기
                                   if (number_cnt > 9)
                                   {
                                          index[location] = number_cnt / 10 + '0';
                                          location++;
                                          index[location] = number_cnt % 10 + '0';
                                          location++;
                                   }
                                   else
                                   {
                                          index[location] = number_cnt + '0';
                                          location++;
                                   }
                                   number_cnt++;

                                   // 연산자 삽입
                                   index[location] = input[i];
                                   location++;

                                   // 만약 단항 연산 포함시 체크
                                   if (minus_check == 1)
                                   {
                                          minus_checking[number_cnt - 1] = 1;
                                          minus_check = 0;
                                   }
                                   else
                                   {
                                          minus_checking[number_cnt - 1] = 0;
                                          minus_check = 0;
                                   }
                            }
                     }
              }
              else if (i == strlen(input) - 1)          // 연산자가 뒤에 없을 시 = 마지막 숫자일 때, 알고리즘은 위와 동일
              {
                     if (input[i - 1] == 'h' || input[i - 1] == 'H')
                     {
                            for (int f = 0; data[7 + input[i]][f] != 'N'; f++)
                            {
                                   data[number_cnt][f] = data[input[i] + 7][f];
                                   data[number_cnt][f + 1] = 'N';
                                   number[number_cnt] = f + 1;
                            }
                            if (minus_checking[7 + input[i]] == 1)
                                   minus_checking[number_cnt] = 1;

                            if (number_cnt > 9)
                            {
                                   index[location] = number_cnt / 10 + '0';
                                   location++;
                                   index[location] = number_cnt % 10 + '0';
                                   location++;
                            }
                            else
                            {
                                   index[location] = number_cnt + '0';
                                   location++;
                            }
                            number_cnt++;
                     }
                     else if ('a' <= input[i] && input[i] <= 'e')
                     {

                            for (int f = 0; data[input[i] - 'a' + 51][f] != 'N'; f++)
                            {
                                   data[number_cnt][f] = data[input[i] - 'a' + 51][f];
                                   data[number_cnt][f + 1] = 'N';
                                   number[number_cnt] = f + 1;
                            }
                            if (minus_checking[input[i] - 'a' + 51] == 1)
                            {
                                   minus_checking[number_cnt] = 1;
                            }
                            else
                            {
                                   minus_checking[number_cnt] = 0;
                            }

                            if (number_cnt > 9)
                            {
                                   index[location] = number_cnt / 10 + '0';
                                   location++;
                                   index[location] = number_cnt % 10 + '0';
                                   location++;
                            }
                            else
                            {
                                   index[location] = number_cnt + '0';
                                   location++;
                            }
                            number_cnt++;
                     }
                     else if ('A' <= input[i] && input[i] <= 'E')
                     {
                            for (int f = 0; data[input[i] - 'A' + 51][f] != 'N'; f++)
                            {
                                   data[number_cnt][f] = data[input[i] - 'A' + 51][f];
                                   data[number_cnt][f + 1] = 'N';
                                   number[number_cnt] = f + 1;
                            }

                            if (minus_checking[input[i] - 'A' + 51] == 1)
                            {
                                   minus_checking[number_cnt] = 1;
                            }
                            else
                            {
                                   minus_checking[number_cnt] = 0;
                            }

                            if (number_cnt > 9)
                            {
                                   index[location] = number_cnt / 10 + '0';
                                   location++;
                                   index[location] = number_cnt % 10 + '0';
                                   location++;
                            }
                            else
                            {
                                   index[location] = number_cnt + '0';
                                   location++;
                            }
                            number_cnt++;
                     }
                     else
                     {
                            data_number = 0;
                            for (int f = i; '0' <= input[f] && input[f] <= '9'; f--)
                            {
                                   if (data_number > 29)
                                   {
                                          error(log);
                                          return -1;
                                   }
                                   data[number_cnt][data_number] = input[f];
                                   data_number++;
                            }

                            data_number--;
                            if (data[number_cnt][data_number] == '0' && data_number != 0)
                            {
                                   while (data[number_cnt][data_number] == '0' && data_number != 0)
                                   {
                                          data[number_cnt][data_number] = 'N';
                                          data_number--;
                                   }
                            }
                            data_number++;

                            number[number_cnt] = data_number;
                            data[number_cnt][data_number] = 'N';
                            if (number_cnt > 9)
                            {
                                   index[location] = number_cnt / 10 + '0';
                                   location++;
                                   index[location] = number_cnt % 10 + '0';
                                   location++;
                            }
                            else
                            {
                                   index[location] = number_cnt + '0';
                                   location++;
                            }
                            number_cnt++;

                            if (minus_check == 1)
                            {
                                   minus_checking[number_cnt - 1] = 1;
                                   minus_check = 0;
                            }
                            else
                            {
                                   minus_checking[number_cnt - 1] = 0;
                                   minus_check = 0;
                            }
                     }
              }
       }

       // 인덱스 배열 마지막에 N 부과
       index[location] = 'N';

       // 인덱스의 길이 반환
       return location - 1;
}

int f(int number, char data[][NUMER_MAX_SIZE + 2], char data_Index[], int minus_checking[], int number_cnt[], char a[], char b[], char c[], char d[], char e[], char log[], int minusabcde[])
{
       int i, j, k;
       // 위치 찾기 변수
       int n, m;
       // 인덱스 숫자로 변환 변수
       int n1, n2;
       int size;
       int insert_data = 0;
       int front_checking;
       int counting, multiply_check;
       int num;
       // int atoechecking = 0;
       int movelocation = 0;

       // 변수 삽입인지 체크
       if (data_Index[1] == '=')
       {
              insert_data = 1;
       }

       // * / % 우선순위 연산자 계산
       for (i = 0; i <= number; i++)
       {
              if (data_Index[i] == '*' || data_Index[i] == '/' || data_Index[i] == '%')
              {

                     // * 앞 숫자 찾기
                     for (n = i - 1; n >= 0; n--){
                            if (data_Index[n] != 'N')
                                   break;
                     }
                     // * 뒤 숫자 찾기
                     for (m = i + 1; m <= number; m++){
                            if (data_Index[m] != 'N')
                                   break;
                     }

                     // 인덱스 두자리인지 한자리인지 확인, n1 n2에 인덱스 숫자로 변환해 삽입
                     if ('0' <= data_Index[n - 1] && data_Index[n - 1] <= '9')
                     {
                            n1 = (data_Index[n - 1] - 48) * 10 + (data_Index[n] - 48);
                     }
                     else
                     {
                            n1 = data_Index[n] - 48;
                     }

                     if ('0' <= data_Index[m + 1] && data_Index[m + 1] <= '9')
                     {
                            n2 = (data_Index[m] - 48) * 10 + (data_Index[m + 1] - 48);
                     }
                     else
                     {
                            n2 = data_Index[m] - 48;
                     }

                     if (data_Index[i] == '*')
                     {

                            // 계산된 숫자의 위치 체크
                            front_checking = 0;

                            // 만약 둘 중 하나의 수가 0이라면
                            if ((data[n1][0] == '0' && data[n1][1] == 'N') || (data[n2][0] == '0' && data[n2][1] == 'N'))
                            {
                                   data[n1][0] = '0';
                                   data[n1][1] = 'N';
                                   front_checking = 1;
                            }
                            else if (number_cnt[n1] > number_cnt[n2])        // 숫자의 크기 비교해 더 큰수를 앞쪽으로 하여 multiply에 집어넣기
                            {
                                   multiply(n1, n2, data);
                                   front_checking = 1;
                            }
                            else if (number_cnt[n1] < number_cnt[n2])
                            {
                                   multiply(n2, n1, data);
                                   front_checking = 2;
                            }
                            else
                            {
                                   size = number_cnt[n1];
                                   while (size >= 0)
                                   {
                                          if (data[n1][size] > data[n2][size])
                                          {
                                                 multiply(n1, n2, data);
                                                 front_checking = 1;
                                                 break;
                                          }
                                          else if (data[n1][size] < data[n2][size])
                                          {
                                                 multiply(n2, n1, data);
                                                 front_checking = 2;
                                                 break;
                                          }
                                          size--;
                                   }
                                   if (size == -1)      // 만약 두 수가 동일하다면
                                   {
                                          multiply(n1, n2, data);
                                          front_checking = 1;
                                   }
                            }

                            // 단항 -체크
                            if (minus_checking[n1] == 1 || minus_checking[n2] == 1)
                            {
                                   if (minus_checking[n1] == 1 && minus_checking[n2] == 1)
                                   {
                                          minus_checking[n1] = 0;
                                          minus_checking[n2] = 0;
                                   }
                                   else
                                   {
                                          if (front_checking == 1)
                                          {
                                                 minus_checking[n1] = 1;
                                                 minus_checking[n2] = 0;
                                          }
                                          else
                                          {
                                                 minus_checking[n1] = 0;
                                                 minus_checking[n2] = 1;
                                          }
                                   }
                            }
                     }
                     else if (data_Index[i] == '/')
                     {
                            front_checking = 1;  // 나누기는 무조건 앞쪽에 숫자 들어가게 연산

                            // 둘 중 하나라도 음수라면
                            if (minus_checking[n1] == 1 || minus_checking[n2] == 1)
                            {
                                   if (minus_checking[n1] == 1 && minus_checking[n2] == 1) // 둘 다 음수라면
                                   {
                                          minus_checking[n1] = 0;
                                          minus_checking[n2] = 0;
                                   }
                                   else  // 둘 중 하나만 음수라면
                                   {
                                          minus_checking[n1] = 1;
                                          minus_checking[n2] = 0;
                                   }
                            }

                            // 크기체크 (앞이 크면 진행, 뒤가 크면 0, 뒤가 0이면 오류반환)
                            if (data[n2][0] == '0' && data[n2][1] == 'N')
                            {
                                   error(log);
                                   return 0;
                            }
                            else
                            {
                                   if (number_cnt[n1] > number_cnt[n2])
                                          divide(n1, n2, data, number_cnt);
                                   else if (number_cnt[n1] < number_cnt[n2])
                                   {
                                          data[n1][0] = '0';
                                          data[n1][1] = 'N';
                                   }
                                   else
                                   {
                                          size = number_cnt[n1];
                                          while (size >= 0)
                                          {
                                                 if (data[n1][size] > data[n2][size])
                                                 {
                                                        divide(n1, n2, data, number_cnt);
                                                        break;
                                                 }
                                                 else if (data[n1][size] < data[n2][size])
                                                 {
                                                        data[n1][0] = '0';
                                                        data[n1][1] = 'N';
                                                        break;
                                                 }
                                                 size--;
                                          }
                                          if (size == -1)
                                          {
                                                 // printf("SIZE\n");
                                                 data[n1][0] = '1';
                                                 data[n1][1] = 'N';
                                          }
                                   }
                            }
                     }
                     else  // % 연산자
                     {
                            front_checking = 1;
                            // 단항 -체크 (음수면 오류 반환)
                            if (minus_checking[n1] == 1 || minus_checking[n2] == 1)
                            {
                                   error(log);
                                   return 0;
                            }

                            // 크기체크 (앞이 크면 진행, 뒤가 크면 앞의 수 그대로, 뒤가 0이면 오류반환)
                            if (data[n2][0] == '0' && data[n2][1] == 'N')
                            {
                                   error(log);
                                   return 0;
                            }
                            else
                            {
                                   if (number_cnt[n1] > number_cnt[n2])
                                          remain(n1, n2, data, number_cnt);
                                   else if (number_cnt[n1] < number_cnt[n2])
                                   {
                                   }
                                   else
                                   {
                                          size = number_cnt[n1];
                                          while (size >= 0)
                                          {
                                                 if (data[n1][size] > data[n2][size])
                                                 {
                                                        remain(n1, n2, data, number_cnt);
                                                        break;
                                                 }
                                                 else if (data[n1][size] < data[n2][size])
                                                 {
                                                        break;
                                                 }
                                                 size--;
                                          }
                                          if (size == -1)
                                          {
                                                 data[n1][0] = '0';
                                                 data[n1][1] = 'N';
                                          }
                                   }
                            }
                     }

                     data_Index[i] = 'N';

                     // 숫자가 어디로 들어갔는지 체크
                     if (front_checking == 1)    // 앞쪽이라면 연산자와 뒤의 인덱스 지움
                     {
                            if (n2 > 9 && !(n2 >= 51 && n2 <= 55))
                            {
                                   data_Index[m] = 'N';
                                   data_Index[m + 1] = 'N';
                            }
                            else
                                   data_Index[m] = 'N';
                            for (counting = 0; data[n1][counting] != 'N'; counting++)
                                   number_cnt[n1] = counting + 1;
                     }
                     else if (front_checking == 2)      // 뒤쪽이라면 연산자와 앞의 인덱스 지움
                     {
                            if (n1 > 9 && !(n1 >= 51 && n1 <= 55))
                            {
                                   data_Index[n] = 'N';
                                   data_Index[n - 1] = 'N';
                            }
                            else
                                   data_Index[n] = 'N';
                            for (counting = 0; data[n2][counting] != 'N'; counting++)
                                   number_cnt[n2] = counting + 1;
                     }
              }
       }

       // + - 나머지 연산자 계산
       for (i = 0; i <= number; i++)
       {
              if (data_Index[i] == '+' || data_Index[i] == '-')
              {

                     front_checking = 0;
                     for (n = i - 1; n >= 0; n--){
                            if (data_Index[n] != 'N')
                                   break;
                     }
                     for (m = i + 1; m <= number; m++){
                            if (data_Index[m] != 'N')
                                   break;
                     }

                     if ('0' <= data_Index[n - 1] && data_Index[n - 1] <= '9')
                     { // 두자리수라면
                            n1 = (data_Index[n - 1] - 48) * 10 + (data_Index[n] - 48);
                     }
                     else
                     { // 한자리수라면
                            n1 = data_Index[n] - 48;
                     }

                     if ('0' <= data_Index[m + 1] && data_Index[m + 1] <= '9')
                     {
                            n2 = (data_Index[m] - 48) * 10 + (data_Index[m + 1] - 48);
                     }
                     else
                     {
                            n2 = data_Index[m] - 48;
                     }

                     if (data_Index[i] == '+')
                     {
                            // 단항 -체크 (-있으면 minus로 보내주기)

                            // 둘 다 음수라면 음수확인 체크 후 더해주기
                            if (minus_checking[n1] == 1 && minus_checking[n2] == 1)
                            {
                                   plus(n1, n2, data);
                                   front_checking = 1;
                            }
                            else
                            {
                                   // 둘 중 하나만 음수라면
                                   if (minus_checking[n1] == 1 || minus_checking[n2] == 1)
                                   {
                                          // 크기비교하여 음수인지 양수인지 확인, 연산
                                          if (number_cnt[n1] > number_cnt[n2])
                                          {
                                                 minus(n1, n2, data);
                                                 front_checking = 1;
                                          }
                                          else if (number_cnt[n1] < number_cnt[n2])
                                          {
                                                 minus(n2, n1, data);
                                                 front_checking = 2;
                                          }
                                          else
                                          {
                                                 size = number_cnt[n1];
                                                 while (size >= 0)
                                                 {
                                                        if (data[n1][size] > data[n2][size])
                                                        {
                                                               minus(n1, n2, data);
                                                               front_checking = 1;
                                                               break;
                                                        }
                                                        else if (data[n1][size] < data[n2][size])
                                                        {
                                                               minus(n2, n1, data);
                                                               front_checking = 2;
                                                               break;
                                                        }
                                                        size--;
                                                 }
                                                 if (size == -1)      // 두 수의 크기가 동일하면 0 삽입
                                                 {
                                                        minus_checking[n1] = 0;
                                                        data[n1][0] = '0';
                                                        data[n1][1] = 'N';
                                                        front_checking = 1;
                                                 }
                                          }
                                   }
                                   else   // 둘 다 양수라면
                                   {
                                          plus(n1, n2, data);
                                          front_checking = 1;
                                   }
                            }
                     }
                     else  // - 연산
                     {
                            // 단항 -체크 (-있으면 +로 보내주기), 크기체크 -> 큰수가 앞으로가게 보내주고 음수체크

                            // 둘 다 음수라면
                            if (minus_checking[n1] == 1 && minus_checking[n2] == 1)
                            {
                                   if (number_cnt[n1] > number_cnt[n2])      // 크기비교하여 음수 양수인지 판단 및 계산
                                   {
                                          minus(n1, n2, data);
                                          front_checking = 1;
                                   }
                                   else if (number_cnt[n1] < number_cnt[n2])
                                   {
                                          minus(n2, n1, data);
                                          front_checking = 2;
                                          minus_checking[n2] = 0;
                                   }
                                   else
                                   {
                                          size = number_cnt[n1];
                                          while (size >= 0)
                                          {
                                                 if (data[n1][size] > data[n2][size])
                                                 {
                                                        minus(n1, n2, data);
                                                        front_checking = 1;
                                                        break;
                                                 }
                                                 else if (data[n1][size] < data[n2][size])
                                                 {
                                                        minus(n2, n1, data);
                                                        front_checking = 2;
                                                        minus_checking[n2] = 0;
                                                        break;
                                                 }
                                                 size--;
                                          }
                                          if (size == -1)
                                          {
                                                 data[n1][0] = '0';
                                                 data[n1][1] = 'N';
                                                 front_checking = 1;
                                                 minus_checking[n1] = 0;
                                          }
                                   }
                            }
                            else
                            {
                                   if (minus_checking[n1] == 1 || minus_checking[n2] == 1)        // 둘 중 하나만 음수라면 더해준 후 부호체크
                                   {
                                          plus(n1, n2, data);
                                          front_checking = 1;
                                   }
                                   else  // 둘 다 양수이면 크기비교하여 부호판단
                                   {
                                          if (number_cnt[n1] > number_cnt[n2])
                                          {
                                                 minus(n1, n2, data);
                                                 front_checking = 1;
                                          }
                                          else if (number_cnt[n1] < number_cnt[n2])
                                          {
                                                 minus(n2, n1, data);
                                                 front_checking = 2;
                                                 minus_checking[n2] = 1;
                                          }
                                          else
                                          {
                                                 size = number_cnt[n1];
                                                 while (size >= 0)
                                                 {
                                                        if (data[n1][size] > data[n2][size])
                                                        {
                                                               minus(n1, n2, data);
                                                               front_checking = 1;
                                                               break;
                                                        }
                                                        else if (data[n1][size] < data[n2][size])
                                                        {
                                                               minus(n2, n1, data);
                                                               front_checking = 2;
                                                               minus_checking[n2] = 1;
                                                               break;
                                                        }
                                                        size--;
                                                 }
                                                 if (size == -1)
                                                 {
                                                        data[n1][0] = '0';
                                                        data[n1][1] = 'N';
                                                        front_checking = 1;
                                                 }
                                          }
                                   }
                            }
                     }

                     data_Index[i] = 'N';

                     // 우선순위 연산자와 동일 방식
                     if (front_checking == 1)
                     {
                            if (n2 > 9 && !(n2 >= 51 && n2 <= 55))
                            {
                                   data_Index[m] = 'N';
                                   data_Index[m + 1] = 'N';
                            }
                            else
                                   data_Index[m] = 'N';
                            for (counting = 0; data[n1][counting] != 'N'; counting++)
                                   number_cnt[n1] = counting + 1;
                     }
                     else if (front_checking == 2)
                     {
                            if (n1 > 9 && !(n1 >= 51 && n1 <= 55))
                            {
                                   data_Index[n] = 'N';
                                   data_Index[n - 1] = 'N';
                            }
                            else
                                   data_Index[n] = 'N';
                            for (counting = 0; data[n2][counting] != 'N'; counting++)
                                   number_cnt[n2] = counting + 1;
                     }
              }
       }

       // 삽입하는 명령어 였다면
       if (insert_data == 1)
       {
              // 남아있는 인덱스 체크
              for (i = 2; i <= number; i++)
              {
                     if (data_Index[i] != 'N')
                            break;
              }

              // 인덱스의 위치 정수형으로 변환
              if (data_Index[i] == 'h')
                     movelocation = data_Index[i + 1] + 7;
              else if (data_Index[i] >= 'a' && data_Index[i] <= 'e')
                     movelocation = data_Index[i] - 46;
              else if (data_Index[i + 1] >= '0' && data_Index[i + 1] <= '9')
              {
                     movelocation = (data_Index[i] - 48) * 10 + data_Index[i + 1] - 48;
              }
              else
                     movelocation = data_Index[i] - 48;

              // 정리하여 삽입
              for (num = 0; data[movelocation][num] != 'N'; num++)
              {
                     data[data_Index[0] - 46][num] = data[movelocation][num];
              }
              data[data_Index[0] - 46][num] = 'N';
              number_cnt[data_Index[0] - 46] = num;

              // 부호 확인
              if (minus_checking[movelocation] == 1)
              {
                     minus_checking[data_Index[0] - 46] = 1;
              }
              else
              {
                     minus_checking[data_Index[0] - 46] = 0;
              }

              // a~e 배열에도 삽입
              if (data_Index[0] == 'a')
              {
                     for (j = 0; data[51][j] != 'N'; j++)
                     {
                            a[j] = data[51][j];
                            a[j + 1] = 'N';
                            number_cnt[51] = j + 1;
                            minusabcde[0] = minus_checking[51];
                     }
              }
              else if (data_Index[0] == 'b')
              {
                     for (j = 0; data[52][j] != 'N'; j++)
                     {
                            b[j] = data[52][j];
                            b[j + 1] = 'N';
                            number_cnt[52] = j + 1;
                            minusabcde[1] = minus_checking[52];
                     }
              }
              else if (data_Index[0] == 'c')
              {
                     for (j = 0; data[53][j] != 'N'; j++)
                     {
                            c[j] = data[53][j];
                            c[j + 1] = 'N';
                            number_cnt[53] = j + 1;
                            minusabcde[2] = minus_checking[53];
                     }
              }
              else if (data_Index[0] == 'd')
              {
                     for (j = 0; data[54][j] != 'N'; j++)
                     {
                            d[j] = data[54][j];
                            d[j + 1] = 'N';
                            number_cnt[54] = j + 1;
                            minusabcde[3] = minus_checking[54];
                     }
              }
              else if (data_Index[0] == 'e')
              {
                     for (j = 0; data[55][j] != 'N'; j++)
                     {
                            e[j] = data[55][j];
                            e[j + 1] = 'N';
                            number_cnt[55] = j + 1;
                            minusabcde[4] = minus_checking[55];
                     }
              }
       }

       return 1;
}

void remain(int front, int back, char data[][NUMER_MAX_SIZE + 2], int num_count[])
{
       int i = 0, front_cnt = num_count[front] - 1, back_cnt = num_count[back] - 1, divide_start, result, cnt = 0, check = 1, check_cnt, k;
       char dataTotal[100];

       divide_start = front_cnt;

       while (check > 0)
       {
              for (k = divide_start; k >= divide_start - back_cnt; k--)
              { // 숫자 크기비교

                     if (data[front][k] > data[back][k - divide_start + back_cnt] || (k == divide_start - back_cnt && data[front][k] == data[back][k - divide_start + back_cnt]))
                     { // 나누는 수는 기준으로 삼아 그 자리수의 해당되는 수와 비교해 크다면 그대로 작다면 자리수를 +1해서 빼기반복
                            check_cnt = 0;
                            result = divide_minus(front, back, divide_start, back_cnt, back_cnt, data); // 어디서 나누는지 시작위치, 나눠지는 수의 범위, 나누는 수의 범위, 숫자 넣어있는 배열 전송
                            break;
                     }
                     else if (data[front][k] == data[back][k - divide_start + back_cnt])
                            continue;
                     else
                     {
                            check_cnt = 1;
                            result = divide_minus(front, back, divide_start, back_cnt + 1, back_cnt, data);
                            break;
                     }
              }

              if (result == 0)
                     break;

              check++;
              for (k = divide_start; k >= 0; k--)
              { // 다 소진되지 않은 즉, 0이 아닌 숫자 찾아 시작지점으로 만들기
                     if (data[front][k] != '0')
                     {
                            divide_start = k;
                            break;
                     }
              }
              if (divide_start - back_cnt < 0)
                     check = 0;
       }

       // 모두 0인지 확인
       for (k = num_count[front] - 1; data[front][k] == '0'; k--)
              ;
       if (k == -1)
       {
              data[front][0] = '0';
              data[front][1] = 'N';
       }
       else
       {
              data[front][k + 1] = 'N';
       }
}

int plus(int front, int back, char data[][NUMER_MAX_SIZE + 2])
{
       int dataTotal[100] = {
           0,
       };
       int i = 0, sum, j;

       // 둘 중 하나의 자리가 끝날 때 까지
       while (data[front][i] != 'N' && data[back][i] != 'N')
       {
              // 두 수 더해서 10 이상이면 다음자리에 더함, 남은 수는 지금의 자릿수에 더함
              sum = data[front][i] + data[back][i] - 96;
              dataTotal[i] += sum % 10;
              if (dataTotal[i] >= 10)     // 만약 현재 자릿수에 더한수가 10이 넘으면 다음자리에 숫자 넣어주기
              {
                     dataTotal[i + 1] += dataTotal[i] / 10;
                     dataTotal[i] %= 10;
              }
              dataTotal[i + 1] += sum / 10;
              i++;
       }

       // 남은 수 판단하여 더해주기
       if (data[front][i] != 'N')
       {
              while (data[front][i] != 'N')
              {
                     dataTotal[i] += data[front][i] - 48;
                     i++;
              }
       }
       else if (data[back][i] != 'N')
       {
              while (data[back][i] != 'N')
              {
                     dataTotal[i] += data[back][i] - 48;
                     i++;
              }
       }

       // 끝자리에도 수가 있는지 없는지 판별하여 data front자리에 잘 넣어주기
       if (dataTotal[i] > 0)
       {
              for (j = 0; j <= i; j++)
                     data[front][j] = dataTotal[j] + '0';
              data[front][j] = 'N';
       }
       else
       {
              for (j = 0; j < i; j++)
              {
                     data[front][j] = dataTotal[j] + '0';
              }
              data[front][j] = 'N';
       }

       return front;
}

void multiply(int front, int back, char data[][NUMER_MAX_SIZE + 2])
{
       int result[NUMER_MAX_SIZE + NUMER_MAX_SIZE] = {
           0,
       };
       int num1[NUMER_MAX_SIZE] = {
           0,
       };
       int num2[NUMER_MAX_SIZE] = {
           0,
       };
       int num1Size;
       int num2Size;
       int tmp;
       for (num1Size = 0; data[front][num1Size] != 'N'; num1Size++)
              ;
       for (num2Size = 0; data[back][num2Size] != 'N'; num2Size++) // 뒤에 있는 숫자 카운팅
              ;

       if (num2Size >= num1Size)
       {
              tmp = num1Size;
              num1Size = num2Size;
              num2Size = tmp;
       }

       for (int i = 0; i < num1Size; i++)
       {
              num1[i] = data[front][i] - '0';
       }
       for (int i = 0; i < num2Size; i++)
       {
              num2[i] = data[back][i] - '0';
       }

       for (int i = 0; i < num2Size; i++)
       {
              for (int j = 0; j < num1Size; j++)
              {
                     result[i + j] += (num2[i] * num1[j]) % 10;
                     result[i + j + 1] += (num2[i] * num1[j]) / 10;
              }
       }

       for (int i = 0; i < num1Size + num2Size; i++)
       {
              if (result[i] >= 10)
              {

                     result[i + 1] += result[i] / 10;
                     result[i] -= (result[i] / 10) * 10;
              }
       }

       for (int i = num1Size + num2Size; i >= 0; i--)
       {
              if (i == num1Size + num2Size)
              {
                     data[front][i] = 'N';
                     continue;
              }
              if (result[i] == 0 && i == num1Size + num2Size - 1)
              {
                     data[front][i] = 'N';
                     continue;
              }
              data[front][i] = result[i] + '0';
       }
}

void minus(int front, int back, char data[][NUMER_MAX_SIZE + 2])
{
       int subtract_after[NUMER_MAX_SIZE] = {
           0,
       };
       int temp_result = 0, front_max = 0, back_max = 0, data_max = 0;

       for (int i = 0; data[front][i] != 'N'; i++)
       {
              front_max++; // 앞에꺼 자릿수 구하는 반복문
       }

       for (int i = 0; data[back][i] != 'N'; i++)
       {
              back_max++; // 뒤에꺼 자릿수 구하는 반복문
       }

       int frontNum[front_max];
       int backNum[back_max];

       for (int i = 0; i < front_max; i++)
       {
              frontNum[i] = data[front][i] - '0';
       }

       for (int i = 0; i < back_max; i++)
       {
              backNum[i] = data[back][i] - '0';
       }

       for (int i = 0; i < front_max; i++)
       {
              temp_result = frontNum[i];
              if (i < back_max)
              {
                     temp_result = temp_result - backNum[i];
              }
              // 빼기 결과 저장
              subtract_after[i] += temp_result;
              if (subtract_after[i] < 0)
              {
                     subtract_after[i] += 10;
                     subtract_after[i + 1] -= 1;
              }
       }

       int i;
       for (i = 0; i < front_max; i++)
       {
              data[front][i] = subtract_after[i] + '0';
       }

       for (; i >= 0; i--)
       {
              if (data[front][i] == '0' && data[front][i + 1] == 'N' && i != 0)
              {
                     data[front][i] = 'N';
              }
       }
}

int divide_minus(int front, int back, int start, int front_count, int back_count, char data[][NUMER_MAX_SIZE + 2])
{
       int i = 0, j, check = 0, tmp, front_location, compare;
       char dataTotal[100];

       while (check == 0)   // 무한반복
       {
              // 크기 판별
              if (start < front_count)
                     return i; // 나누는 수보다 나눌 수가 더 작으면 return
              compare = back_count;
              if (front_count > back_count)
              { // 나눌 수가 나누는 수보다 자릿수가 더 크면
                     if (data[front][start] == '0')
                     { // 앞자리 수가 0이어야 크기 판단
                            for (j = start - 1; j >= start - front_count; j--)
                            {
                                   if (data[front][j] < data[back][compare])
                                   { // 다음자리수 비교
                                          return i;
                                   }
                                   else if (data[front][j] > data[back][compare])
                                          break;
                                   compare--;
                            }
                     }
              }
              else
              {
                     // 자릿수가 동일하면 앞자리 0 확인 안하고 크기 판단
                     for (j = start; j >= start - front_count; j--)
                     {
                            if (data[front][j] < data[back][compare])
                            { // 다음자리수 비교
                                   return i;
                            }
                            else if (data[front][j] > data[back][compare])
                                   break;
                            compare--;
                     }
              }

              // 빼기 반복
              front_location = start - front_count; // 기준 수의 맨 뒷자리수부터 빼기 시작
              for (int back_location = 0; back_location <= back_count; back_location++)
              { // back(연산자 뒤의 숫자) 맨 뒷자리수부터 빼기
                     if (data[front][front_location] < data[back][back_location])
                     { // 숫자비교, 만약 끝자리 수가 타 수보다 더 작다면?
                            for (j = front_location + 1; j <= start; j++)
                            { // 0이 아닌 수를 찾아 숫자 뺏어오기
                                   if (data[front][j] - 48 > 0)
                                   {
                                          data[front][j]--;                            // 0이 아닌 부분 1빼기
                                          for (int k = j - 1; k > front_location; k--) // 숫자 뺏어오며 생기는 나머지 수 보충
                                                 data[front][k] += 9;
                                          break;
                                   }
                            }
                            tmp = data[front][front_location] - data[back][back_location] + 10; // 계산
                            data[front][front_location] = tmp + '0';                            // 숫자 정리
                     }
                     else
                     {
                            tmp = data[front][front_location] - data[back][back_location];
                            data[front][front_location] = tmp + '0';
                     }

                     front_location++;
              }

              i++;
       }
       return i;
}

void divide(int front, int back, char data[][NUMER_MAX_SIZE + 2], int num_count[])
{
       int i = 0, divide_start, result, cnt = 0, check = 1, check_cnt, k;
       int front_cnt = num_count[front] - 1, back_cnt = num_count[back] - 1; // 인덱스로 활용할 것이기에 길이에서 1 빼주기
       char dataTotal[100];

       divide_start = front_cnt; // 시작점을 끝으로 잡아주기 (reverse로 제작했기에 숫자의 첫번째 자리를 의미)

       while (check > 0)
       {
              for (k = divide_start; k >= divide_start - back_cnt; k--)
              { // 숫자 크기비교

                     // 나누는 수는 기준으로 삼아 그 자리수의 해당되는 수와 비교해 크다면 그대로 작다면 자리수를 +1해서 빼기반복
                     if (data[front][k] > data[back][k - divide_start + back_cnt] || (k == divide_start - back_cnt && data[front][k] == data[back][k - divide_start + back_cnt]))
                     { 
                            check_cnt = 0;
                            result = divide_minus(front, back, divide_start, back_cnt, back_cnt, data); // 어디서 나누는지 시작위치, 나눠지는 수의 범위, 나누는 수의 범위, 숫자 넣어있는 배열 전송
                            break;
                     }
                     else if (data[front][k] == data[back][k - divide_start + back_cnt])
                            continue;
                     else
                     {
                            check_cnt = 1;
                            result = divide_minus(front, back, divide_start, back_cnt + 1, back_cnt, data);
                            break;
                     }
              }

              if (result == 0)
                     break;

              if (check_cnt == 1)
              { // 자릿수에 맞추어 숫자 넣어주기
                     if (check == 1)
                            dataTotal[divide_start - back_cnt] = 'N';
                     dataTotal[divide_start - back_cnt - 1] = result + '0';
                     cnt = divide_start - back_cnt - 1;
              }
              else
              {
                     if (check == 1)
                            dataTotal[divide_start - back_cnt + 1] = 'N';
                     dataTotal[divide_start - back_cnt] = result + '0';
                     cnt = divide_start - back_cnt;
              }

              check++;
              for (k = divide_start; k >= 0; k--)
              { // 다 소진되지 않은 즉, 0이 아닌 숫자 찾아 시작지점으로 만들기
                     if (data[front][k] != '0')
                     {
                            divide_start = k;
                            break;
                     }
              }
              if (divide_start - back_cnt < 0)
                     check = 0;
       }

       for (k = 0; dataTotal[k] != 'N'; k++)
       { // 비어있는 자리수에 0을 넣어주며 front에 숫자 정리.
              if (dataTotal[k] >= '0' && dataTotal[k] <= '9')
                     data[front][k] = dataTotal[k];
              else
                     data[front][k] = '0';
       }
       data[front][k] = 'N';
}
