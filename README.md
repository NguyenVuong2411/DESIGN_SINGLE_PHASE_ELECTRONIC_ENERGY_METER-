Ý tưởng thiết kế
=
**Khối dòng điện**:

- _Phần 1_ đưa tín hiệu vào mạch khuyếch đại để điều chỉnh tỷ lệ điện áp phù hợp sau đó đưa vào trong Khối xử lý tín hiệu để thực hiện nhân.

- _Phần 2_ đưa tín hiệu vào mạch chỉnh lưu bán kỳ âm sử dụng Opamp để đưa tín hiệu AC về dạng DC. Sau đó đưa vào kênh ADC của Khối vi điều khiển để đọc và hiển thị giá trị dòng điện hiệu dụng.

**Khối điện áp**: Khối điện áp sử dụng biến áp để hạ áp từ mạch tải tiêu thụ xuống mức điện áp phù hợp. Khối gồm có 2 phần:
- _Phần 1_ đưa tín hiệu vào mạch phân áp để điều chỉnh tỷ lệ điện áp phù hợp sau đó đưa vào trong Khối xử lý tín hiệu để thực hiện nhân.

- _Phần 2_ đưa tín hiệu vào mạch chỉnh lưu bán kỳ âm sử dụng Opamp để đưa tín hiệu AC về dạng DC. Sau đó đưa vào kênh ADC của Khối vi điều khiển để đọc và hiển thị giá trị điện áp hiệu dụng. 


**Khối xử lý tín hiệu**: Tín hiệu điện từ khối điện áp và khối dòng điện được đưa vào khối xử lý tính hiệu để thực hiện phép nhân analog cho ra tín hiệu điện áp có giá trị tỉ lệ với công suất trung bình P. Tiếp tục chuyển đổi tín hiệu điện áp này thành tín hiệu tần số tương ứng để đưa vào Khối vi điều khiển để tính toán và hiển thị giá trị điện năng tiêu thụ trên mạch tải

- _IC nhân tín hiệu AD633_: IC thực hiện chức năng nhân analog hai tín hiệu điện áp tức thời và dòng điện tức thời, cho kết quả tín hiệu đầu ra là tín hiệu điện áp tỷ lệ với tín hiệu công suất tức thời.

- _Bộ lọc thông thấp_: Thực hiện lọc thông thấp loại bỏ thành phần tín hiệu có tần số 2ωt của tín hiệu từ ngõ ra của AD633 để cho ra tín hiệu điện áp tỷ lệ với tín hiệu công suất trung bình.

- _IC chuyển đổi điện áp – tần số LM331_: Chuyển đổi tín hiệu điện áp sau khi được lọc thông thấp thành tín hiệu có tần số tỷ lệ. Sau đó đưa tín hiệu tần số vào Khối vi điều khiển để thực hiện tính toán điện năng tiêu thụ.

**Khối vi điều khiển**: Thực hiện các hoạt động đọc giá trị ADC của các đại lượng dòng điện, điện áp và giá trị tần số từ Khối xử lý tín hiệu để tính toán và hiển thị lên Khối LCD các đại lượng dòng điện, điện áp hiệu dụng, hệ số công suất và số điện năng tiêu thụ. Đồng thời cũng lưu giá trị điện năng tiêu thụ vào bộ nhớ FLASH phòng trường hợp mất điện. Từ hệ số công tơ điện tính toán được từ thiết kế, Khối vi điều khiển sẽ xuất tín hiệu điều khiển LED chớp với tần số tương ứng với hệ số công tơ điện imp/kWh. Bên cạnh đó, Khối vi điều khiển cũng giao tiếp với Module ESP8266 gửi dữ liệu lên web để quan sát.

**Khối Node MCU ESP8266**: Kết nối mạng với wifi và giao tiếp với Khối vi điều khiển thông qua UART, nhận dữ liệu và gửi lên trang web để quan sát. 

**Khối hiển thị LCD 20x4**: Thực hiện chức năng hiển thị các đại lượng điện cần đo. 

**Đèn LED**: Được điều khiển bởi Khối vi điều khiển để chớp theo tần số của hệ số công tơ điện. 

Hoạt động
=
- Vi điều khiển sẽ thực hiện thiết lập các hệ số tính toán các giá trị điện áp, dòng điện, chỉ số kWh
- Khởi tạo màn hình LCD và các Timer1 để đếm số xung và Timer 2 tạo delay 15s
- Đọc giá trị kWh được lưu trong bộ nhớ FLASH của vi điều khiển.
- Tiếp tục công việc hiển thị và đọc và tính toán ADC các giá trị dòng, áp.
- Timer đếm đủ số lượng xung tương ứng với 0.25Wh thì sẽ lặp tức ngắt để đảo trạng thái LED và tăng số Wh thêm 0.25 đơn vị. Vì vậy, chu kỳ LED sáng và tắt sẽ tương ứng với 0.5Wh.
- Timer thứ 2 sẽ thực hiện ngắt để lưu dữ liệu vào giá trị Wh vào FLASH và gửi giá trị dòng điện và Wh đến ESP8266 thông qua UART để hiển thị lên web.

**_Link Video Demo_**: https://drive.google.com/file/d/120e9Vy7E5JAveWMTcmhampzS1fTwQ8PU/view?usp=sharing
