# code-trr
Thư viện đồ thị

Thư viện được xây dựng dựa bời nhóm sinh viên: Trần Nam Dương - 20194535, Nguyễn Đồng Đức Anh - 20194473, Nguyễn Hải Dương - 20194530

Có sử dụng thư viện hỗ trợ của thầy Nguyễn Bá Ngọc: https://github.com/bangoc/cgraph

Ý tưởng: Thêm thư viện graphlib.h và mã nguồn graphlib.c có chứa các hàm liên quan tới thuật toán trên đồ thị vào thư viện cgraph và hợp nhất để mở rộng thư viện gốc chứa thêm các thuật toán đã học trong môn Toán Rời Rạc

Được hỗ trợ biên dịch bằng cmake và ninja qua file CMakeLists.txt
VD file CMakeLists.txt:

add_executable(tenfilethucthi tenfile.c)
add_subdirectory(cgraph)
target_link_libraries(tenfilethucthi cgraph)

Các file dữ liệu test nằm trong thư mục Test Data có tên ứng với từng thuật toán (hàm) trong thư viện