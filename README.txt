# Hướng Dẫn Cài Đặt và Mở Dự Án PlatformIO

## 📌 Mục Tiêu

Hướng dẫn người mới cách:

* Cài đặt **Visual Studio Code** và **PlatformIO**
* Clone mã nguồn từ **GitHub**
* Mở dự án và biên dịch bằng **PlatformIO**

---

## ⚙️ Yêu Cầu

* Hệ điều hành: Windows / macOS / Linux
* Kết nối Internet

---

## 1⃣️ Cài Đặt Visual Studio Code

1. Truy cập: [https://code.visualstudio.com/](https://code.visualstudio.com/)
2. Tải về và cài đặt VS Code theo hướng dẫn hệ điều hành của bạn.

---

## 2⃣️ Cài Extension PlatformIO

1. Mở VS Code
2. Vào menu: `View` → `Extensions` (hoặc nhấn `Ctrl + Shift + X`)
3. Tìm từ khóa: `PlatformIO IDE`
4. Chọn extension có biểu tượng **con kiến màu cam** → Nhấn **Install**

📍 Sau khi cài xong, VS Code sẽ khởi động lại.

---

## 3⃣️ Clone Mã Nguồn từ Git

Nếu bạn có link GitHub (ví dụ):

```
https://github.com/yourusername/ten-du-an.git
```

### Trên VS Code:

1. Mở Command Palette: `Ctrl + Shift + P`
2. Gõ `Git: Clone` → Chọn
3. Dán đường link Git
4. Chọn thư mục để lưu dự án

👉 VS Code sẽ hỏi có muốn mở thư mục vừa clone không → Chọn **Open**.

### Hoặc dùng dòng lệnh (nếu đã cài Git):

```bash
git clone https://github.com/yourusername/ten-du-an.git
cd ten-du-an
code .
```

---

## 4⃣️ Mở Dự Án với PlatformIO

1. Mở thư mục chứa dự án đã clone
2. Đảm bảo thấy file `platformio.ini` trong thư mục gốc (file cấu hình dự án)
3. PlatformIO sẽ tự nhận diện dự án
4. Vào **PlatformIO Toolbar** (góc dưới trái):

   * Nhấn biểu tượng ✅ để **Build**
   * Nhấn biểu tượng 🔼 để **Upload**
   * Nhấn biểu tượng 📄 để mở **Serial Monitor**

---

## ✅ Lưu Ý

* Nếu gặp lỗi lần đầu build, hãy kiểm tra:

  * Đã chọn đúng board trong `platformio.ini` chưa? (VD: `board = esp32dev`)
  * Cáp USB đã kết nối chưa?
  * Cổng COM đúng chưa? (có thể chỉnh trong menu `Devices` của PlatformIO)

---

## 📞 Hỗ Trợ

Nếu gặp vấn đề, bạn có thể:

* Đọc hướng dẫn tại: [https://docs.platformio.org](https://docs.platformio.org)
* Hoặc tạo issue tại repository GitHub

---

🛠 Chúc bạn cài đặt thành công và phát triển dự án dễ dàng!
