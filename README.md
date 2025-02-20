Today I Learned
=============

Reinforcement Learning
-------------

- 2024.09.02
    - 강화학습 이론&실습   
        - 1장 환경설정   
        윈도우 버전 anaconda, jupyter notebook 설치   
        RL_scratch 가상환경 설정
        - 2장 사전 지식   
        머신러닝, 강화학습 개념   
        기초 수학: 기초 선형 대수 ~벡터연산까지   

- 2024.09.04
    - 파이썬과 케라스로 배우는 강화학습
        - 1장 강화학습 개요   
            - 강화학습 개념   
            행동심리학과 강화학습, 머신러닝과 강화학습 간의 연관성, '강화'라는 개념   
            - 강화학습 문제   
            강화학습은 순차적 행동 결정 문제에 적용   
            - 강화학습의 예시:브레이크아웃   
            브레이크아웃의 MDP와 학습방법   
        - 2장 강화학습 기초1:MDP와 벨만방정식   
            - MDP   
            상태, 행동, 보상함수, 상태변환확률, 할인율, 정책   
            - 가치함수   
            반환값 G, 가치함수 v(s), 큐함수 q(s,a)   

- 2024.09.05   
    - 파이썬과 케라스로 배우는 강화학습   
        - 2장 강화학습 기초1:MDP와 벨만방정식   
            - 벨만 방정식   
            현재 상태의 가치함수와 다음 상태 가치함수의 관계식을 정의한 것.   
            벨만 기대 방정식, 벨만 최적 방정식   
        - 3장 강화학습 기초2:그리드월드와 다이내믹 프로그래밍   
            - 다이내믹 프로그래밍과 그리드 월드   
            쿤 문제를 바로 푸는 것이 아닌 작은 문제들을 풀어나감   
            정책 이터레이션, 가치 이터레이션   
            - 다이내믹 프로그래밍1: 정책 이터레이션   
            정책 평가 -> 정책 발전   
- 2024.09.06   
    - 파이썬과 케라스로 배우는 강화학습   
        - 3장 강화학습 기초2:그리드월드와 다이내믹 프로그래밍   
            - 다이내믹 프로그래밍2: 가치 이터레이션   
            명시적인 정책/내재적인 정책   
            벨만 최적방정식과 가치 이터레이션   
            - 다이내믹 프로그래밍의 한계   
            계산 복잡도, 차원의 저주, 환경에 대한 완벽한 정보 필요   
            - 강화학습   
            모델 없이 환경과의 상호작용을 통해 입력과 출력 사이의 관계를 학습   
        - 4장 강화학습 기초3:그리드월드와 큐러닝   
            - 강화학습과 정책 평가 1: 몬테카를로 예측   
            기댓값을 샘플링을 통한 평균으로 대체하는 기법   
            에피소드 하나를 진행하고 에피소드 동안 지나온 상태의 반환값을 구함   
            반환값은 하나의 샘플이 되어 각 상태의 가치함수를 업데이트   
            - 강화학습과 정책 평가 2:시간차 예측   
            몬테카를로와 달리 타임스텝마다 큐함수를 업데이트 / 벨만 기대 방정식 이용   
            - 강화학습 알고리즘 1: 살사   
            강화학습 제어에서 행동 선택 시 가치함수룰 사용하면 환경의 모델을 알아야 하기 때문에 큐함수를 사용   
            시간차 제어에서는 하나의 샘플로 (s,a,r,s',a')가 필요. 시간차제어를 살사라고 함   
            - 강화학습 알고리즘 2: 큐러닝   
            살사:온폴리시 / 큐러닝:오프폴리시(온폴리시의 단점을 개선)   
            큐함수 업데이트에 벨만 최적방정식 이용   
        - 5장 강화학습 심화 1: 그리드월드와 근사함수   
            - 근사함수   
            몬테카를로, 살사, 큐러닝 -> 테이블 방식의 한계 -> 근사함수를 통한 가치함수의 매개변수화를 해야함   
            - 인공신경망   
            노드, 활성함수   
            - 딥러닝 : 높은 추상화   
            심층 신경망이 스스로 특징 추출   
            - 신경망의 학습 - 오차함수(Lose Function), 역전파 알고리즘(편미분을 이용해 가중치, 편향 업데이트), 경사 하강법(변수: 학습 속도)   
- 2024.09.07   
    - 파이썬과 케라스로 배우는 강화학습   
        - 5장 강화학습 심화 1: 그리드월드와 근사함수   
            - 인공신경망 라이브러리: 케라스   
            텐서플로 2.0 내부의 케라스 모듈   
            - 딥살사   
            큐함수 테이블 대신 큐함수를 인공신경망으로 근사, 인공신경망을 업데이트 할 때 경사 하강법 사용,   
            오차함수는 MSE를 사용하여 정의, 엡실론-그리디 정책, 상태는 입력이고 출력은 각 행동에 대한 큐함수인 인공신경망인 모델   
            - 폴리시 그레디언트   
            정책 기반 강화학습, 인공신경망이 정책을 직접적으로 근사, 입력은 상태이고 출력은 각 행동을 할 확률,   
            누적 보상은 최적화하고자 하는 목표함수, 변수는 인공신경망의 가중치, 목표 함수 미분을 활용한 최대화->경사 상승법,   
            큐함수를 반환값으로 대체하는 것 : REINFORCE 알고리즘, 오류함수 = 크로스 엔트로피*반환값   
- 2024.09.08   
    - 파이썬과 케라스로 배우는 강화학습   
        - 6장 강화학습 심화 2: 카트폴   
            - 알고리즘 1: DQN   
            오프폴리시 알고리즘인 큐러닝+인공신경망   
            경험 리플레이 사용->메모리 간의 상관관계 없앰, 학습 안정적, 메모리를 매 타임스텝마다 학습에 사용   
            타겟신경망 사용->목표가 되는 정답이 계속 변하는 부트스트랩의 문제점 해결, 타겟신경망은 일정 시간 간격마다 업데이트   
            오류함수로 MSE 사용, 오류함수를 최소로 하는 방향으로 인공신경망 업데이트   
            - 알고리즘 2: 액터-크리틱   
            REINFORCE 알고리즘의 단점을 해결하기 위해 다이내믹 프로그래밍의 정책 이터레이션 구조를 사용   
            크리틱 : 큐함수/가치함수를 근사(가치신경망), 정책을 평가, 오류함수는 시간차에러(어드밴티지 함수)   
            액터 : 정책을 근사(정책신경망), 오류함수는 크로스엔트로피*시간차 에러   
            어드밴티지 함수 : 큐함수-가치함수. 큐함수의 변화 정도를 줄여주기 위한 베이스라인.   
            어드밴티지 액터-크리틱 : A2C   
            연속적 액터-크리틱 : 연속적 확률 분포 정책->정규분포 사용(평균, 표준편차), 정책 신경망의 출력을 평균과 표준편차로 사용   
        - 7장 강화학습 심화 3: 아타리   
            - 브레이크아웃 DQN   
            컨볼루션 신경망: 게임화면이 인공신경망의 입력 -> 입력벡터의 크기가 매우 커짐.   
            컨볼루션 필터 - 이미지 노이즈를 없애거나 어떤 특징을 강조할 때 사용   
            컨볼루션 층 생성 시 설정할 것 : 필터의 개수, 필터의 크기, 컨볼루션 연산 시 필터가 이동하는 폭:stride, 활성함수   
            DQN 학습 전 이미지 전처리 : 그레이 스케일 -> 이미지 사이즈 축소, 프레임 스킵, 연속된 4개의 행동은 하나의 히스토리   
            - 브레이크아웃 A3C   
            DQN의 한계: 많은 메모리 수는 느린 학습 속도의 원인이 됨. 오프폴리시 강화학습을 사용해야 한다는 단점이 있음.   
            A3C: 메모리에 많은 샘플을 쌓는 것이 아닌, 에이전트를 여러개 사용하여 샘플 사이의 연관성을 깸   
            샘플을 모으는 각 에이전트인 액터러너가 글로벌신경망을 업데이트하고, 자신을 글로벌신경망으로 업데이트.   
            여러개의 액터러너가 이 과정을 비동기적(Asynchronous)으로 진행하므로 A3C   
            파이썬에서 멀티쓰레딩을 사용하여 여러 에이전트를 사용   
- 2024.10.04   
    - University Lecture   
        - Chapter01.Mathematical Preliminaries   
- 2024.10.08   
    - University Lecture   
        - Quiz1 Study   
            - Chapter01.Mathematical Preliminaries   
- 2024.10.09   
    - University Lecture   
        - Quiz1 Study   
            - Chapter01.Mathematical Preliminaries ~ Chapter02.Markov Decision Process and Bellman Equations   
- 2024.10.30   
    - University Lecture   
        - Study   
            - Chapter02.Markov Decision Process and Bellman Equations ~ Chapter03.Dynamic Programming   
- 2024.10.31   
    - University Lecture   
        - Study   
            - Chapter01.Mathematical Preliminaries ~ Chapter03.Dynamic Programming   
- 2024.11.16   
    - University Lecture   
        - HW1   
- 2024.11.19   
    - University Lecture   
        - Study   
            - Chapter04.Model Free Prediction ~ Chapter05.Model Free Control   
- 2024.11.30   
    - University Lecture   
        - HW2   
- 2024.12.3   
    - University Lecture   
        - Study   
            - Chapter07.Value Function Approximation   
- 2024.12.18   
    - University Lecture   
        - Term Project   
- 2024.12.19   
    - University Lecture   
        - Term Project   
- 2024.12.20   
    - University Lecture   
        - Term Project   
        

Python Study
-------------

- 2024.09.14   
    - 스타트업 파이썬   
    Chapter1.파이썬 시작하기 ~ Chapter8.반복문   
- 2024.09.14   
    - 스타트업 파이썬   
    Chapter9.리스트 자료형 ~ Chapter12.사전 자료형   
- 2024.09.14   
    - 스타트업 파이썬   
    Chapter13.함수   
- 2024.09.21   
    - 스타트업 파이썬   
    Chapter14.파일 입출력 ~ Chapter17.클래스와 객체 지향 개념   
    


AI Programming
-------------

- 2024.09.17   
    - Python   
    numpy, pandas   
- 2024.10.21   
    - Study   
    Python Lecture01_Variable_and_Operator ~ DL_Lecture08_Optimization   
- 2024.11.17   
    - Study   
    DL_Lecture1_ML_&_Linear_Algebra ~ DL_Lecture6_Model_Selection   
- 2024.11.22   
    - Study   
    모두의 딥러닝: 1장 ~ 6장   
    DL_Lecture1_ML_&_Linear_Algebra ~ DL_Lecture4_Logistic_Regression   
- 2024.11.23   
    - Study   
    모두의 딥러닝: 7장 ~ 16장   
    DL_Lecture5_Classification ~ DL_Lecture11_CNN_Implementation   
- 2024.12.1   
    - Study   
    모두의 딥러닝: 17장 ~ 19장   
- 2024.11.9   
    - Study   
    DL_Lecture1_ML_&_Linear_Algebra ~ DL_Lecture20_Generative_Models3   
- 2024.12.11   
    - Study   
    DL_Lecture1_ML_&_Linear_Algebra ~ DL_Lecture20_Generative_Models3   
    

Engineering Mathematics   
-------------

- 2024.09.19   
    - 7장 푸리에 해석학   
    7.1 직교함수 ~ 7.3 스튀름-리우빌 이론   
- 2024.09.20   
    - 7장 푸리에 해석학   
    7.4 베셀과 르장드르 급수   
- 2024.09.28   
    - 7장 푸리에 해석학   
    7.1 ~ 7.4 연습문제   
    - 과제1   
        - 7장 푸리에 해석학   
- 2024.10.3   
    - 7장 푸리에 해석학 복습   
    - 8장 편미분 방정식 예습   
- 2024.10.10   
    - 9장 적분 변환 방법 예습   
- 2024.10.11   
    - 공학수학1 복습   
        - 1장 미분 방정식의 개요 ~ 3장 4절 고계 선형 미분 방정식-미정 계수법   
    - 과제2   
        - 8장 편미분 방정식   
- 2024.10.12
    - 과제2   
        - 8장 편미분 방정식   
- 2024.10.17   
    - 9장 적분 변환 방법 예습   
- 2024.10.18   
    - 9장 적분 변환 방법 복습   
    - 과제3   
        - 9장 적분 변환 방법   
- 2024.10.19   
    - 9장 적분 변환 방법 복습   
    - 과제3   
        - 9장 적분 변환 방법   
- 2024.10.23   
    - 7장 푸리에 해석학 복습   
- 2024.10.24   
    - 7장 푸리에 해석학 ~ 9장 적분 변환 방법 복습   
- 2024.11.1   
    - 10장 복소수와 복소 해석 함수   
- 2024.11.6   
    - 10장 복소수와 복소 해석 함수   
- 2024.11.14   
    - 10장 복소수와 복소 해석 함수   
- 2024.11.15   
    - 10장 복소수와 복소 해석 함수   
- 2024.11.16   
    - 과제4   
        - 10장 복소수와 복소 해석 함수   
- 2024.11.28   
    - 11장 복소 적분   
- 2024.11.29   
    - 11장 복소 적분   
    - 과제5   
        - 11장 복소 적분   
- 2024.11.30   
    - 과제5   
        - 11장 복소 적분   
    - 과제6   
        12장 급수와 유수   
- 2024.12.11   
    - 과제6   
        12장 급수와 유수   
- 2024.12.12   
    - 10장 복소수와 복소 해석 함수 ~ 12장 급수와 유수   

Computer Vision
-------------

- 2024.09.24   
    - Homework1   
    Color Transform   
- 2024.09.29   
    - Homework2   
    Contrast Transform   
- 2024.09.30   
    - Homework3   
    Morphology, labeling   
- 2024.10.13   
    - Study   
    03.Camera Geometry ~ 12.Image Subsampling   
    - Homework4   
    Morphology   
- 2024.10.14   
    - Homework4   
    Morphology   
- 2024.10.15   
     - Study   
    10.Histogram Transform ~ 13.Edge Extraction   
- 2024.10.16   
    - Homework5   
    Histogram Transform   
- 2024.10.18   
     - Study   
    03.Camera Geometry   
- 2024.10.19   
     - Study   
    04.Color Transform ~ 06.Otsu's Algorithm   
- 2024.10.20   
     - Study   
    07.Labeling, Morphology ~ 14.Canny Operator   
- 2024.10.22   
     - Study   
    03.Camera Geometry ~ 14.Canny Operator   
- 2024.11.4   
     - Study   
        - 컴퓨터비전   
        Chapter02.영상처리   
- 2024.11.5   
     - Study   
    15.Corner Detection ~ 17.Generalized Hough Transform   
- 2024.11.20   
     - Study   
    15.Corner Detection ~ 19.SIFT Description   
- 2024.11.21   
    - Homework6   
    Hough Transform   
- 2024.11.22   
    - Homework6   
    Hough Transform   
- 2024.11.25   
    - Homework7   
    Generalized Hough Transform   
- 2024.11.26   
    - Homework7   
    Generalized Hough Transform   
    - Study   
        - 컴퓨터비전   
        Chapter03.에지 검출 ~ Chapter04.지역 특징 검출   
- 2024.12.3   
     - Study   
    22.Optical Flow ~ 23.Image Warping   
- 2024.12.9   
     - Project   
- 2024.12.18   
     - Study   
    15.Corner Detection ~ 25.Bird Eye View   


Control System Design
-------------

- 2024.10.02   
    - study   
    Chapter1 Sysyem Identification ~ Chapter2 Linear Algebra   
- 2024.10.06   
    - Quiz1 Study   
    Chapter1 Sysyem Identification ~ Chapter2 Linear Algebra   
- 2024.10.07   
    - Quiz1 Study   
    Chapter1 Sysyem Identification ~ Chapter2 Linear Algebra   
- 2024.10.16   
    - study   
    Chapter2 Linear Algebra   
- 2024.10.17   
    - study   
    Chapter7 State Space Design   
- 2024.10.25   
    - study   
    Chapter7 State Space Design   
- 2024.10.26   
    - study   
    Chapter1 Sysyem Identification ~ Chapter7 State Space Design   
- 2024.10.27   
    - study   
    Chapter7 State Space Design   
- 2024.10.28   
    - study   
    Chapter1 Sysyem Identification ~ Chapter7 State Space Design   
- 2024.10.29   
    - study   
    Chapter1 Sysyem Identification ~ Chapter7 State Space Design   
- 2024.11.18   
    - study   
    Chapter7 State Space Design   
- 2024.11.21   
    - study   
    Chapter7 State Space Design   
- 2024.11.28   
    - study   
    Chapter7 State Space Design   
- 2024.11.30   
    - Homework1   
    Chapter7 State Space Design   
- 2024.12.2   
    - study   
    Chapter7 State Space Design   
- 2024.12.4   
    - study   
    Chapter7 State Space Design   
- 2024.12.13   
    - study   
    Chapter7 State Space Design   
- 2024.12.14   
    - study   
    Chapter7 State Space Design   
- 2024.12.15   
    - study   
    Chapter7 State Space Design   
- 2024.12.16   
    - study   
    Chapter7 State Space Design   

Machine Learning
-------------

- 2024.10.14   
    - Study   
    Chapter02.Nunpy/Pandas ~ Chapter03.Scikit-learn   
- 2024.10.15   
    - Study   
    Chapter04.Evaluation ~ Chapter05.Classification   
    - Homework1   
    Decision Tree   
- 2024.11.02   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater01.파이썬 기반의 머신러닝과 생태계 이해   
- 2024.11.3   
    - Homework2   
    차원 축소   
- 2024.11.04   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater02.사이킷런으로 시작하는 머신러닝   
- 2024.11.08   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater02.사이킷런으로 시작하는 머신러닝   
- 2024.11.09   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater04.분류   
- 2024.11.10   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater04.분류   
- 2024.11.11   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater04.분류   
- 2024.11.12   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater04.분류   
- 2024.12.6   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater03.평가   
- 2024.12.7   
    - Study   
        - 파이썬 머신러닝 완벽 가이드   
        Chpater06.차원 축소 ~ Chpater07.군집화   
- 2024.12.8   
    - Study   
    Chapter04.Evaluation ~ Chapter10.Clustering   

Python Programming
-------------

- 2025.01.06   
    - 1일차.파이썬 소개 및 환경설정   
- 2025.01.07   
    - 2일차.프로그래밍 기초   
- 2025.01.08   
    - 3일차.제어문과 조건식   
- 2025.01.09   
    - 4일차.리스트와 딕셔너리   
- 2025.01.10   
    - 5일차.반복문   
- 2025.01.13   
    - 6일차.함수   
- 2025.01.14   
    - 7일차.함수2   
- 2025.01.15   
    - 8일차.자료구조와 알고리즘   
- 2025.01.16   
    - 9일차.클래스(1)   
- 2025.01.17   
    - 10일차.클래스(2)   
- 2025.01.20   
    - 11일차.tkinter   
- 2025.01.21   
    - 12일차.파일 처리   
- 2025.01.22   
    - 13일차.예외 처리, 문자열, 람다 함수, map 함수   
- 2025.01.23   
    - 14일차.정규표현식   
- 2025.01.24   
    - 15일차.고급함수   
- 2025.01.31   
    - 16일차.알고리즘(1)   
- 2025.02.03   
    - 17일차.알고리즘(2)   
- 2025.02.04   
    - 18일차.그래픽스 지원 API   
- 2025.02.05   
    - 19일차.딥러닝 파이썬 패키지(1)   
    - 복습   
        - 1.파이썬 소개 및 환경설정   
- 2025.02.06   
    - 20일차.딥러닝 파이썬 패키지(2)   
    - 복습   
        - 2.프로그래밍 기초 ~ 3.제어문과 조건식   
- 2025.02.07   
    - 21일차.딥러닝 파이썬 패키지(3)   
    - 복습   
        - 4.리스트와 딕셔너리 ~ 6.함수   
- 2025.02.10   
    - 22일차.Python 활용 심화 (1)   
    - 복습   
        - 7.함수2 ~ 19.딥러닝 파이썬 패키지(1)   
- 2025.02.11   
    - 23일차.Python 활용 심화 (2)   
    - 복습   
        - 20.딥러닝 파이썬 패키지(2) ~ 21.딥러닝 파이썬 패키지(3)   

DevOps
-------------

- 2025.02.12   
    - 24일차.DBMS1   
- 2025.02.13   
    - 25일차.DBMS2   
- 2025.02.14   
    - 26일차.GIT   
- 2025.02.17   
    - 27일차.Docker 활용   

AI
-------------

- 2025.02.18   
    - 28일차.python   
- 2025.02.19   
    - 29일차.EDA   
- 2025.02.20   
    - 30일차.pytorch   
        
Coding Test
-------------

- 2025.01.22   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 4문제   
- 2025.01.23   
    - Programmers   
        - Lv.0 9문제   
- 2025.01.25   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.26   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.27   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.28   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.29   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.30   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.01.31   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.02.03   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.02.04   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   
- 2025.02.05   
    - Programmers   
        - Lv.0 9문제   
        - Lv.1 1문제   

