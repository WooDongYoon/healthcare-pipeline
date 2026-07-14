#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include "stackL.h"

typedef struct blood_pressure
{
	int systole;	//수축기
	int diastole;	//이완기
	int year;		//혈압 자료 획득 년도
	int status;		//0:정상,1:비정상, 2:재측정
}bp;

int main()
{
	FILE* p1 = fopen("out_bloodpressure.txt", "r");		//혈압 내용이 적혀있는 입력파일
	FILE* p2 = fopen("result.txt", "w+");				//출력파일
	if (p1 == NULL || p2 == NULL)
	{
		printf("파일 열기 오류");
		return 0;
	}

	int num;
	fscanf(p1, "%d", &num);
	printf("검사횟수 = %d\n", num);
	bp* pressure = (bp*)malloc(sizeof(bp) * num);

	int i = 0;
	while (!feof(p1))
	{

		if (fscanf(p1, "%d  %d  %d", &(pressure + i)->systole, &(pressure + i)->diastole, &(pressure + i)->year) != 3)
		{
			break;  // 3개 못읽으면 종료
		}


		int s = (pressure + i)->systole;
		int d = (pressure + i)->diastole;
		int pulse = s - d;  // 맥압(수축기 혈압과 이완기 혈압의 차이값)->코드에서는 측정 오류 판별용

		// 판정
		if (d >= s)                              // 수치 역전
			(pressure + i)->status = 2;           // 재측정
		else if (pulse < 20 || pulse > 100)     // 맥압 이상
			(pressure + i)->status = 2;           // 재측정
		else if (s < 70 || d < 40)             // 너무 낮음
			(pressure + i)->status = 2;           // 재측정
		else if (s >= 180 || d >= 110)         // 너무 높음
			(pressure + i)->status = 2;           // 재측정
		else if (s <= 129 && d <= 79)          // 정상
			(pressure + i)->status = 0;
		else                                    // 비정상 (주의)
			(pressure + i)->status = 1;

		push((pressure + i)->status);
		i++;
	}

	fprintf(p2, "\t\t\t\t    이완기  수축기  상태\n");
	for (int j = i-1; j>=0; j--)		//오래된 자료부터 저장하기 때문에 역순으로 출력
	{
		int status = pop();
		char result[30];
		if (status == 0)
		{
			strcpy(result, "정상");
		}
		else if (status == 1)
		{
			strcpy(result, "비정상");
		}
		else
		{
			strcpy(result,"재측정필요");
		}
		fprintf(p2, "%d번째 검사(%d년도) 결과: %-10d %-6d %-4s\n", j + 1, (pressure + j)->year, (pressure + j)->systole, (pressure + j)->diastole, result);
	}

	fclose(p1);
	fclose(p2);
	free(pressure);
	system("notepad.exe result.txt");
}