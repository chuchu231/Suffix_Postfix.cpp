# Tính giá trị biểu thức trung tố
### Nội dung bài tập
Cho biểu thức trung tố được lưu trữ trên tập tin văn bản infix.txt. Biểu thức được viết trên 1 dòng và kết
thúc bởi 1 enter. Các toán hạng, toán tử và dấu thay đổi ưu tiên toán tử cách nhau bởi 1 khoảng trắng.
- Đọc chuỗi biểu thức từ tập tin
- Kiểm tra tính hợp lệ của biểu thức
- Tính giá trị của biểu thức (nếu hợp lệ)
- Xuất kết quả ra tập tin văn bản result.txt theo định dạng:
  + Dòng đầu chứa số 1 nếu biểu thức hợp lệ và 0 nếu ngược lại
  + Dòng tiếp theo chứa giá trị tính được của biểu thức nếu hợp lệ hoặc chuỗi văn bản thông báo chi tiết về lỗi nếu ngược lại.

Trong đó:
- Các toán tử được hổ trợ gồm: cộng (+), trừ (-), nhân (*), chia (/), modulo (% - chỉ áp dụng cho số nguyên) và lũy thừa (^)
- Các dấu thay đổi độ ưu tiên toán tử: “(” và “)”
- Các toán hạng gồm: số nguyên âm/dương và số thực âm/dương

Mục tiêu bài tập
- Cài đặt các thao tác cơ bản của ngăn xếp
- Vận dụng các thao tác đọc ghi file văn bản
- Vận dụng các thao tác xử lý chuỗi
- Hiện thực hóa chương trình tính giá trị biểu thức trung tố
