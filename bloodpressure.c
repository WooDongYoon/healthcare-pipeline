/*다음부터는 그냥 이 코드에서 나오는 출력 코드는 데이터만 써놓고 다음코드에서 fsanf받는게 더 편할듯*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct blood_pressure
{
	int systole;	//수축기
	int diastole;	//이완기
	int year;		//혈압 자료 획득 년도
}bp;

int main()
{
	srand((unsigned int)time(NULL));		//매번 다른 난수
	FILE* fp = fopen("out_bloodpressure.txt", "w+");
	if (fp == NULL)
	{
		printf("파일 열기 오류");
		return 0;
	}
	int num;
	printf("검사횟수는? :");
	scanf("%d", &num);
	bp* p = (bp*)malloc(sizeof(bp) * num);
	fprintf(fp, "%d\n", num);				//검사횟수 healthcare.c에 넘겨주기
	for (int i = 0; i < num; i++)
	{
		(p + i)->systole = rand() % 171 + 50;	//수축기 혈압 범위 50~220	
		(p + i)->diastole = rand() % 121 + 20;	//이완기 혈압 범위 20~140
		(p + i)->year = rand() % 67 + 1960;		//혈압을 잰 년도 범위 1960~2026
	}

	// 2단계: 년도 기준 정렬 (생성 다 끝난 후!)
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - 1 - i; j++) {
			if ((p + j)->year > (p + j + 1)->year) {
				bp temp = *(p + j);
				*(p + j) = *(p + j + 1);
				*(p + j + 1) = temp;
			}
		}
	}

	for (int i = 0; i < num; i++)
	{
		fprintf(fp, "%d     %d     %d\n", (p + i)->systole, (p + i)->diastole, (p + i)->year);
	}

	free(p);
	fclose(fp);
	system("notepad.exe out_bloodpressure.txt");
}