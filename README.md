# healthcare-pipeline
스택을 배우며 파이프라인으로 구현한 헬스케어 코드  

# Healthcare Pipeline

혈압 데이터를 생성하고 판정하는 2단계 파이프라인 프로그램입니다.

## 개요

난수로 혈압 데이터를 생성해 파일에 저장하고, 다음 단계에서 읽어 스택으로 판정 결과를 출력합니다.

## 파이프라인 구조

```
bloodpressure.c
    난수로 혈압 데이터 생성 (수축기, 이완기, 년도)
    년도 기준 버블 정렬
    out_bloodpressure.txt 저장
        ↓
healthcare.c
    out_bloodpressure.txt 읽기
    맥압 기반 판정 -> 스택에 push
    스택 pop으로 역순 출력
    result.txt 저장
```

## 판정 기준

| 조건 | 판정 |
|------|------|
| 수축기 <= 129 and 이완기 <= 79 | 정상 |
| 수치 역전 / 맥압 이상 / 범위 초과 | 재측정 필요 |
| 그 외 | 비정상 |

맥압(수축기 - 이완기)이 20 미만이거나 100 초과이면 재측정으로 판정합니다.

## 자료구조

- **스택 (stackL)**: 연결 리스트 기반 LIFO 구조
  - 판정 결과를 push -> pop으로 역순 출력
  - 년도 오름차순 정렬 데이터를 최신순으로 출력하기 위해 사용

## 파일 구조

```
├── bloodpressure.c       # 혈압 난수 생성 및 파일 저장
├── healthcare.c          # 혈압 판정 및 결과 출력
├── stackL.c              # 스택 구현
└── stackL.h              # 스택 헤더
```

## 실행 순서

1. `bloodpressure.c` 실행 -> 검사 횟수 입력 -> `out_bloodpressure.txt` 생성
2. `healthcare.c` 실행 -> 판정 결과 -> `result.txt` 생성

## 개발 환경

- Visual Studio 2022
- C언어 (C89)
