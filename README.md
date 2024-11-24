# **Hệ Thống Quản Lý Thư Viện**  
### *Dự án cho môn Cấu Trúc Dữ Liệu & Giải Thuật (CTDL & GT)*  

---

## **Tổng Quan Dự Án**  
Dự án này xây dựng một **Hệ Thống Quản Lý Thư Viện** nhằm hỗ trợ các hoạt động hàng ngày của thư viện, bao gồm:  
- Quản lý mượn và trả sách.  
- Tìm kiếm thông tin sách.  
- Quản lý hiệu quả thông tin sách, bạn đọc và phiếu mượn.  

Hệ thống đảm bảo mọi dữ liệu được lưu trữ và truy xuất từ file.  

---

## **Thông Tin Chính**  
- **Mã Dự Án**: `PRO_CTDL_3`  
- **Hình Thức Nộp**: Nộp qua Google Classroom.  
- **Hạn Chót**: 29 / 11 / 2024  
- **Phạm Vi**: Bao gồm các chương 2, 3, 4 và 5 của môn học.  

---

## **Chuẩn Đầu Ra Cần Đạt**  
- Hiểu rõ cách quản lý dữ liệu dựa trên file.  
- Thực hành các kỹ thuật cấu trúc dữ liệu như mảng, danh sách và hàng đợi.  
- Triển khai các thuật toán tìm kiếm, cập nhật và quản lý dữ liệu.  
- Áp dụng cơ chế kiểm soát truy cập và xử lý lỗi.  

---

## **Tính Năng Hệ Thống**  

### **1. Xác Thực Người Dùng**  
**Màn Hình Đăng Nhập**:  
- Người dùng phải nhập tài khoản và mật khẩu hợp lệ được lưu trong file `Admin.txt`.  
- Khóa tài khoản sau 3 lần đăng nhập sai.  
- Có thể thoát hệ thống bằng cách nhấn phím **ESC**.  

**Bảo Mật**:  
- Mật khẩu được ẩn dưới dạng `*` trong quá trình nhập để đảm bảo tính bảo mật.  

---

### **2. Menu Chính**  
Sau khi đăng nhập thành công, menu chính cung cấp các tùy chọn sau:  
1. **Quản Lý Sách**  
2. **Quản Lý Phiếu Mượn**
3. **Quản lý Bạn Đọc**

---

### **3. Quản Lý Sách**  
Quản lý kho sách của thư viện với các chức năng sau:  

#### **3.1 Hiển Thị Danh Sách Sách**  
- Hiển thị thông tin chi tiết của tất cả sách, bao gồm:  
  - **Trường Dữ Liệu**: Mã sách, Tên sách, Tác giả, Nhà xuất bản, Giá bán, Năm xuất bản, Số trang, Ngày nhập kho, Tình trạng.  

#### **3.2 Thêm Sách**  
- Thêm sách mới vào hệ thống.  
- **Kiểm Tra**:  
  - Đảm bảo mã sách không trùng lặp.  
- **Cập Nhật**:  
  - Dữ liệu sách mới được ghi nối tiếp vào file `Sach.txt`.  

#### **3.3 Xóa Sách**  
- Xóa sách bằng cách nhập mã sách.  
- **Điều Kiện**:  
  - Tình trạng sách phải là `0` (không được mượn).  
  - Sách phải tồn tại trong thư viện.  
- **Cập Nhật**:  
  - Dữ liệu được ghi lại vào file `Sach.txt`.  

---

### **4. Quản Lý Phiếu Mượn**  
Xử lý hiệu quả việc mượn và trả sách:  

#### **4.1 Hiển Thị Phiếu Mượn**  
- Hiển thị tất cả phiếu mượn được lưu trong file `PhieuMuon.txt`.  

#### **4.2 Mượn Sách**  
- Nhập mã sách và mã bạn đọc để tạo phiếu mượn mới.  
- **Điều Kiện**:  
  - Sách phải không được mượn (tình trạng `0`).  
  - Mã bạn đọc phải tồn tại trong danh sách bạn đọc.  
- **Cập Nhật**:  
  - Tình trạng sách được cập nhật bằng số phiếu mượn.  
  - File `Sach.txt` và `PhieuMuon.txt` được cập nhật.  

#### **4.3 Trả Sách**  
- Nhập số phiếu mượn để trả sách.  
- **Điều Kiện**:  
  - Phiếu mượn phải tồn tại và có tình trạng `1` (đang mượn).  
- **Cập Nhật**:  
  - Tình trạng sách và phiếu mượn được đặt lại là `0`.  
  - File `Sach.txt` và `PhieuMuon.txt` được cập nhật.  

---

## **Yêu Cầu Bổ Sung**  

### **Xử Lý Lỗi**  
- Thông báo lỗi cho người dùng và cho phép họ thử lại hoặc chọn chức năng khác.  
- Đảm bảo các đầu vào hoặc thao tác không hợp lệ được xử lý cẩn thận.  

### **Giao Diện Người Dùng**  
- Sử dụng màu sắc để tăng tính trực quan.  
- Điều hướng đơn giản với các hướng dẫn rõ ràng.  

---

## **Cấu Trúc File**  

### **1. `Sach.txt`**  
Lưu thông tin sách:  
- **Trường Dữ Liệu**: Mã sách, Tên sách, Tác giả, Nhà xuất bản, Giá bán, Năm xuất bản, Số trang, Ngày nhập kho, Tình trạng.  

### **2. `BanDoc.txt`**  
Lưu thông tin bạn đọc:  
- **Trường Dữ Liệu**: Mã bạn đọc, Họ tên, Ngày đăng ký.  

### **3. `PhieuMuon.txt`**  
Lưu thông tin phiếu mượn:  
- **Trường Dữ Liệu**: Số phiếu, Mã bạn đọc, Mã sách, Ngày mượn, Ngày trả, Tình trạng.  

### **4. `Admin.txt`**  
Lưu thông tin tài khoản quản trị:  
- **Trường Dữ Liệu**: Tên tài khoản, Mật khẩu (được mã hóa).  

---

## **Hướng Dẫn Chạy Chương Trình**  
1. Biên dịch và chạy chương trình bằng trình biên dịch hoặc IDE hỗ trợ C++.  
2. Làm theo hướng dẫn để đăng nhập và sử dụng các chức năng hệ thống.  
3. Đảm bảo các file dữ liệu (`Sach.txt`, `BanDoc.txt`, `PhieuMuon.txt`, và `Admin.txt`) có trong thư mục chương trình.  

---

## **Hướng Phát Triển Trong Tương Lai**  
- Thêm giao diện người dùng đồ họa (GUI) để cải thiện trải nghiệm.  
- Triển khai thông báo nhắc nhở quá hạn trả sách.  
- Thêm chức năng tìm kiếm sách và bạn đọc.    
