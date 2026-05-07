# Dual-Axis-Solar-Tracker
 Hệ thống theo dõi ánh sáng mặt trời 2 trục dùng Arduino

# Mini Dual Axis Solar Tracker

## Overview
Dự án mô phỏng hệ thống theo dõi và bám sát ánh sáng mặt trời 2 trục (Pan & Tilt), giúp tối ưu hóa hiệu suất thu thập năng lượng cho các tấm pin solar, ứng dụng nền tảng vi điều khiển Arduino. 

## Hardware Stack
* Arduino Uno R3
* 4 x LDR (GL5528)
* 4 x Trở (10K ohm, 1/4W sai số 5% 250V)
* 2 x Servo (SG90 180 độ)
* Formex (tự cắt ghép khung)
* Breadboard
* Jumper wires

## Key Technical Features
* **Theo dõi 2 trục (Dual-Axis):** Bám sát nguồn sáng đa hướng (Lên/Xuống, Trái/Phải).
* **Thuật toán Lọc nhiễu tín hiệu (Signal Smoothing):** Sử dụng bộ chia điện áp LDR kết hợp lấy trung bình chéo giúp triệt tiêu hiện tượng giật cục (Oscillation).
* **Khóa an toàn Cơ khí:** Giới hạn góc quay của Servo bằng phần mềm (10° - 170°) giúp chống kẹt và tuôn bánh răng.
* **Ngủ đông thông minh & Soft Homing:** Tự động phát hiện điều kiện thiếu sáng để đi vào chế độ ngủ tiết kiệm điện. Hệ thống sử dụng thuật toán "Soft Homing" (nâng hạ từng độ một có trễ) để đưa tấm pin từ từ về góc hướng Đông đón bình minh, giúp giảm tải đột ngột và bảo vệ bánh răng Servo.
* **Bộ lọc Bóng râm giả (False Darkness Filter):** Tích hợp bộ đếm thời gian (Debounce Timer) để phân biệt giữa trời tối thật và các hiện tượng tối giả tạm thời (như mây đen bay ngang, chim đậu che khuất cảm biến), ngăn chặn hệ thống bị đánh lừa và đi ngủ sai thời điểm.

## Wiring & Setup
<img width="2560" height="1739" alt="z7798401851067_d5dad9149f3f4497db342bc9751ce12c" src="https://github.com/user-attachments/assets/70602c58-e84d-43e6-af7c-fafe638c14a3" />
<img width="1349" height="520" alt="Mini Solar Tracker" src="https://github.com/user-attachments/assets/b4c8b4dc-925d-4ec6-9b98-7e825a49c972" />
<p align="center">Hình ảnh Tindercad mang tính chất minh họa một số linh kiện có thể khác so với mô hình thực tế</p>

<p align="center">*Dự án thực hành Cơ điện tử nền tảng - Đại học Sư phạm Kỹ thuật TP.HCM (HCMUTE) (06/05/2026).* 
</p>
