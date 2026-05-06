#include <Servo.h>

// ==========================================
// 1. KHỞI TẠO ĐỐI TƯỢNG VÀ BIẾN
// ==========================================
Servo servoPan;  
Servo servoTilt; 

int panAngle = 9đ;
int tiltAngle = 90;

int minAngle = 10;
int maxAngle = 170;

// ==========================================
// 2. ĐỊNH NGHĨA CHÂN CẢM BIẾN LDR
// ==========================================
#define LDR_TOP_LEFT A0    
#define LDR_TOP_RIGHT A1   
#define LDR_BOT_LEFT A2    
#define LDR_BOT_RIGHT A3   

// ==========================================
//  KHU VỰC TINH CHỈNH (CHO HỘP 25x25x25)
// ==========================================
int tolerance = 30;       
int sleepThreshold = 150;   // (Nên để về 60)

int homePanAngle = 98;    
int homeTiltAngle = 145;   
bool isAsleep = false;    
int softSpeed = 30;       

//  THÔNG SỐ BỘ LỌC "BÓNG RÂM GIẢ"
int darkCounter = 0;      // Biến đếm thời gian tối liên tục
int confirmTime = 100;    // Số vòng lặp cần thiết để xác nhận là tối thật (100 vòng ~ 3 giây để test)

// ==========================================
// THUẬT TOÁN LỌC NHIỄU (SMOOTHING)
// ==========================================
int readSmooth(int pin) {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(1); 
  }
  return sum / 10; 
}

void setup() {
  Serial.begin(9600); 
  servoPan.attach(9);
  servoTilt.attach(10);
  servoPan.write(panAngle);
  servoTilt.write(tiltAngle);
  Serial.println("Solar Tracker - False Darkness Filter Enabled");
  delay(2000); 
}

void loop() {
  // 3. ĐỌC GIÁ TRỊ QUA BỘ LỌC
  int tl = readSmooth(LDR_TOP_LEFT);
  int tr = readSmooth(LDR_TOP_RIGHT);
  int bl = readSmooth(LDR_BOT_LEFT);
  int br = readSmooth(LDR_BOT_RIGHT);

  // 4. CHẾ ĐỘ NGỦ ĐÔNG & LỌC BÓNG RÂM GIẢ
  int totalLight = (tl + tr + bl + br) / 4;
  
  if (totalLight < sleepThreshold) {
    darkCounter++; // Bắt đầu đếm số vòng lặp bị tối
    
    // Nếu bị tối LIÊN TỤC vượt mức thời gian xác nhận
    if (darkCounter >= confirmTime) {
      if (isAsleep == false) {
        Serial.println("Troi da toi that su! Dang di bo ve huong Dong...");

        // Soft Homing (Ngang)
        while (panAngle != homePanAngle) {
          if (panAngle < homePanAngle) panAngle++;
          else panAngle--;
          servoPan.write(panAngle);
          delay(softSpeed); 
        }

        // Soft Homing (Dọc)
        while (tiltAngle != homeTiltAngle) {
          if (tiltAngle < homeTiltAngle) tiltAngle++;
          else tiltAngle--;
          servoTilt.write(tiltAngle);
          delay(softSpeed);
        }
        
        Serial.println("Da vao vi tri ngu dong.");
        isAsleep = true; 
      }
      delay(100);
      return; // Bỏ qua phần tính toán bên dưới khi đã ngủ
    }
  } else {
    // NẾU CÓ NẮNG LẠI (Đám mây bay đi)
    darkCounter = 0;  // Lập tức xóa nháp bộ đếm về 0
    isAsleep = false; // Thức dậy bám nắng tiếp
  }

  // 5. TÍNH TRUNG BÌNH CÁC CỤM
  int avgTop = (tl + tr) / 2;      
  int avgBot = (bl + br) / 2;      
  int avgLeft = (tl + bl) / 2;     
  int avgRight = (tr + br) / 2;    

  // 6. ĐIỀU KHIỂN TRỤC DỌC
  int diffTilt = avgTop - avgBot; 
  if (abs(diffTilt) > tolerance) {    
    if (avgTop > avgBot) {            
      tiltAngle--; 
    } else if (avgTop < avgBot) {     
      tiltAngle++; 
    }
  }

  // 7. ĐIỀU KHIỂN TRỤC NGANG 
  int diffPan = avgLeft - avgRight; 
  if (abs(diffPan) > tolerance) {     
    if (avgLeft > avgRight) {         
      panAngle--; 
    } else if (avgLeft < avgRight) {  
      panAngle++; 
    }
  }

  // 8. KHÓA GÓC 
  panAngle = constrain(panAngle, minAngle, maxAngle);
  tiltAngle = constrain(tiltAngle, minAngle, maxAngle);

  // 9. THỰC THI
  servoPan.write(panAngle);
  servoTilt.write(tiltAngle);

  delay(27); 
}