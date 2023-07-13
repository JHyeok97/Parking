# **🚗 Parking Management System: 주차를 더욱 쉽게!**


이 프로젝트는 주차장의 주차 및 결제 정보를 관리하는 **주차 관리 시스템**을 구현하는 것을 목표로 합니다. 
주차장에서 발생하는 모든 정보를 한 눈에 볼 수 있게 해주는 이 시스템을 통해, 주차장 관리가 더욱 편리해질 것입니다.

## **🏗️ 구조: MVC 패턴**
![Dw2qq5Kg](https://github.com/JHyeok97/Parking/assets/64429035/5202d2a9-526f-48ef-b9a5-5da7bdf8c845)

이 프로젝트는 **MVC(Model-View-Controller) 패턴**을 따릅니다. 이 패턴은 애플리케이션을 세 가지 역할로 분리하여 코드의 재사용성과 유지보수성을 향상시킵니다.
**main.cpp**: 이는 프로그램의 시작점입니다. Controller 객체를 생성하고 run 메소드를 호출하여 프로그램을 시작합니다.

- **View (View.h / View.cpp)**: 이 파일들은 사용자 인터페이스를 담당합니다. 사용자에게 메뉴를 보여주고, 사용자의 선택을 받아 해당 기능을 실행합니다.
- **Database (Database.h / Database.cpp)**: 이 파일들은 데이터베이스 기능을 담당합니다. 주차장의 정보와 주차된 차량의 정보를 저장하고 관리합니다.
- **Controller (Controller.h / Controller.cpp)**: 이 파일들은 프로그램의 전반적인 흐름을 제어합니다. View로부터 사용자의 입력을 받아, 해당 기능을 Database를 통해 실행하고, 결과를 다시 View를 통해 사용자에게 보여줍니다.

### **파일 구조**

**main.cpp**
이 파일은 프로그램의 시작점입니다. Controller 객체를 생성하고, run() 메소드를 호출하여 프로그램을 시작합니다.

**View.h / View.cpp**

- showMenu(): 사용자에게 메뉴를 보여주고 선택을 받습니다.
- getCarNumber(): 사용자로부터 차량 번호를 입력받습니다.
- showParkingStatus(): 주차장의 현재 상태를 보여줍니다.

**Database.h / Database.cpp**

- addCar(): 차량을 주차장에 추가합니다.
- removeCar(): 주차장에서 차량을 제거합니다.
- getParkingStatus(): 주차장의 현재 상태를 반환합니다.

**Controller.h / Controller.cpp**

- run(): 프로그램을 실행합니다. 사용자의 선택에 따라 적절한 작업을 수행합니다.
- parkCar(): 차량을 주차합니다.
- leaveCar(): 차량을 출차시킵니다.


## **📊 데이터베이스: 주차 정보의 핵심**

이 프로젝트는 주차장의 주차 및 결제 정보를 관리하기 위한 **데이터베이스**를 사용합니다. 
이 데이터베이스는 방문객, 회원, 관리자, 주차 정보, 결제 정보 등에 대한 정보를 포함하는 다양한 테이블을 포함합니다.

![o4EnzZVs](https://github.com/JHyeok97/Parking/assets/64429035/821d86a1-a93a-4128-85c5-22ce0d62dbde)

이 관계도는 다음과 같이 해석할 수 있습니다:
Guest 테이블의 guest_id는 Parking과 Pay 테이블에 연결되어 있습니다.
Members 테이블의 member_id는 Parking 테이블에 연결되어 있습니다.
Parking 테이블의 parking_id는 Pay 테이블에 연결되어 있습니다.

![4SOrzCWj](https://github.com/JHyeok97/Parking/assets/64429035/9440d19f-1edf-4d74-882f-95ad0c1b31e8)

- **Guest**: 방문객을 나타내며, 각각 고유의 ID와 차량 ID를 가집니다.
- **Members**: 회원을 나타내며, 각각 고유의 ID, 차량 ID, 이름, 주소, 전화번호, 만료 날짜를 가집니다.
- **Admin**: 관리자를 나타내며, 각각 고유의 ID, 이름, 전화번호, 이메일을 가집니다.
- **Parking**: 주차 정보를 나타내며, 각각 고유의 ID, 방문객 ID, 회원 ID, 입차 시간, 출차 시간, 주차 상태를 가집니다. 방문객 ID와 회원 ID는 각각 Guest 테이블과 Members 테이블을 참조합니다.
- **Pay**: 결제 정보를 나타내며, 각각 고유의 ID, 주차 ID, 방문객 ID, 주차 요금, 결제 방법, 입차 시간, 출차 시간을 가집니다. 주차 ID는 Parking 테이블을, 방문객 ID는 Guest 테이블을 참조합니다.

방문객(Guest)과 회원(Members)은 각각 주차(Parking) 정보를 가질 수 있으며, 주차(Parking) 정보는 결제(Pay) 정보를 가집니다.

## **🚀 시작하기**

이 프로젝트를 사용하려면, 먼저 데이터베이스를 설정해야 합니다. 
이를 위해 DB/query.txt 파일에 있는 SQL 쿼리를 실행하세요. 
이 쿼리는 데이터베이스 구조를 생성하고, 테스트 데이터를 삽입합니다.
그런 다음, 소스 코드를 컴파일하고 실행하세요. 이 프로젝트는 C++로 작성되었으므로, C++ 컴파일러가 필요합니다.
