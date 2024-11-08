#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

class SinhVien {
private:
    string ma;
    string ten;
    int tuoi;
    float diem;

public:
    // Constructor
    SinhVien() : ma(""), ten(""), tuoi(0), diem(0.0f) {}

    // Nhập dữ liệu
    friend istream& operator>>(istream& in, SinhVien& sinhVien) {
        cout << "Nhập mã sinh viên: ";
        in >> sinhVien.ma;
        cout << "Nhập tên sinh viên: ";
        in.ignore(); // Để bỏ qua ký tự newline
        getline(in, sinhVien.ten);
        cout << "Nhập tuổi: ";
        in >> sinhVien.tuoi;
        cout << "Nhập điểm: ";
        in >> sinhVien.diem;
        return in;
    }

    // Xuất dữ liệu
    friend ostream& operator<<(ostream& out, const SinhVien& sinhVien) {
        out << "Mã: " << sinhVien.ma 
            << ", Tên: " << sinhVien.ten 
            << ", Tuổi: " << sinhVien.tuoi 
            << ", Điểm: " << sinhVien.diem;
        return out;
    }

    // So sánh điểm
    bool operator<(const SinhVien& other) const {
        return diem < other.diem;
    }

    bool operator>(const SinhVien& other) const {
        return diem > other.diem;
    }

    // Các hàm setter
    void setMa(const string& ma) { this->ma = ma; }
    void setTen(const string& ten) { this->ten = ten; }
    void setTuoi(int tuoi) { this->tuoi = tuoi; }
    void setDiem(float diem) { this->diem = diem; }

    // Các hàm getter
    string getMa() const { return ma; }
    string getTen() const { return ten; }
    int getTuoi() const { return tuoi; }
    float getDiem() const { return diem; }
};

class DanhSachSinhVien {
private:
    list<SinhVien> sinhViens;

public:
    void themSinhVien() {
        SinhVien sinhVien;
        cin >> sinhVien;
        sinhViens.push_back(sinhVien);
    }

    void nhapTuBanPhim(int soLuong) {
        for (int i = 0; i < soLuong; ++i) {
            cout << "Nhập thông tin cho sinh viên thứ " << (i + 1) << ":\n";
            themSinhVien();
        }
    }

    void hienThiSinhVien() {
        for (const auto& sinhVien : sinhViens) {
            cout << sinhVien << endl;
        }
    }

    void sapXepSinhVienTangDan() {
        sinhViens.sort();
    }

    void sapXepSinhVienGiamDan() {
        sinhViens.sort(greater());
    }

    void timMax() {
        if (sinhViens.empty()) {
            cout << "Danh sách rỗng." << endl;
            return;
        }
        auto maxSinhVien = *max_element(sinhViens.begin(), sinhViens.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.getDiem() < b.getDiem();
        });
        cout << "Sinh viên có điểm cao nhất: " << maxSinhVien << endl;
    }

    void timMin() {
        if (sinhViens.empty()) {
            cout << "Danh sách rỗng." << endl;
            return;
        }
        auto minSinhVien = *min_element(sinhViens.begin(), sinhViens.end(), [](const SinhVien& a, const SinhVien& b) {
            return a.getDiem() < b.getDiem();
        });
        cout << "Sinh viên có điểm thấp nhất: " << minSinhVien << endl;
    }

    void timSinhVien(const string& ma) {
        auto it = find_if(sinhViens.begin(), sinhViens.end(), [&ma](const SinhVien& sinhVien) {
            return sinhVien.getMa() == ma;
        });
        if (it != sinhViens.end()) {
            cout << "Tìm thấy: " << *it << endl;
        } else {
            cout << "Không tìm thấy sinh viên." << endl;
        }
    }

    void xoaSinhVien(const string& ma) {
        auto it = remove_if(sinhViens.begin(), sinhViens.end(), [&ma](const SinhVien& sinhVien) {
            return sinhVien.getMa() == ma;
        });
        if (it != sinhViens.end()) {
            sinhViens.erase(it, sinhViens.end());
            cout << "Đã xóa sinh viên có mã: " << ma << endl;
        } else {
            cout << "Không tìm thấy sinh viên để xóa." << endl;
        }
    }

    void nhapTuFile(const string& tenFile) {
    ifstream file(tenFile);
    if (!file.is_open()) {
        cout << "Không thể mở file: " << tenFile << endl;
        return;
    }

    int n;
    file >> n; // Đọc số lượng sinh viên
    file.ignore(); // Bỏ qua ký tự newline

    for (int i = 0; i < n; ++i) {
        SinhVien sinhVien;
        string ma, ten;
        int tuoi;
        float diem;

        // Đọc từng thông tin
        getline(file, ma);
        getline(file, ten);
        file >> tuoi;
        file >> diem;
        file.ignore(); // Bỏ qua ký tự newline

        // Gán giá trị cho sinh viên
        sinhVien.setMa(ma);
        sinhVien.setTen(ten);
        sinhVien.setTuoi(tuoi);
        sinhVien.setDiem(diem);

        sinhViens.push_back(sinhVien);
    }

    file.close();
    cout << "Đã nhập " << n << " sinh viên từ file." << endl;
}
};

class App {
private:
    DanhSachSinhVien danhSach;

public:
    void hienThiMenu() {
        int choice;
        do {
            cout << "\n=== MENU QUẢN LÝ SINH VIÊN ===" << endl;
            cout << "1. Nhập danh sách sinh viên từ file" << endl; // Nhập từ file
            cout << "2. Nhập danh sách viên từ bàn phím" << endl; // Nhập nhiều sinh viên
            cout << "3. Hiện thị danh sách sinh viên" << endl;
            cout << "4. Sắp xếp danh sách sinh viên (Tăng dần)" << endl;
            cout << "5. Sắp xếp danh sách sinh viên (Giảm dần)" << endl;
            cout << "6. Tìm sinh viên có điểm cao nhất" << endl;
            cout << "7. Tìm sinh viên có điểm thấp nhất" << endl;
            cout << "8. Tìm sinh viên theo mã" << endl;
            cout << "9. Xóa sinh viên theo mã" << endl; // Xóa sinh viên
            cout << "10. Thêm sinh viên" << endl; // Thêm sinh viên
            cout << "0. Thoát" << endl;
            cout << "Chọn: ";
            cin >> choice;
            cout << endl;

            switch (choice) {
                case 1: { // Nhập danh sách sinh viên từ file
                    string tenFile;
                    cout << "Nhập tên file: ";
                    cin >> tenFile;
                    danhSach.nhapTuFile(tenFile);
                    break;
                }
                case 2: { // Nhập nhiều sinh viên từ bàn phím
                    int soLuong;
                    cout << "Nhập số lượng sinh viên cần thêm: ";
                    cin >> soLuong;
                    danhSach.nhapTuBanPhim(soLuong);
                    break;
                }
                case 3: // Hiện thị danh sách sinh viên
                    danhSach.hienThiSinhVien();
                    break;
                case 4: // Sắp xếp danh sách sinh viên (Tăng dần)
                    danhSach.sapXepSinhVienTangDan();
                    cout << "Đã sắp xếp danh sách sinh viên tăng dần." << endl;
                    break;
                case 5: // Sắp xếp danh sách sinh viên (Giảm dần)
                    danhSach.sapXepSinhVienGiamDan();
                    cout << "Đã sắp xếp danh sách sinh viên giảm dần." << endl;
                    break;
                case 6: // Tìm sinh viên có điểm cao nhất
                    danhSach.timMax();
                    break;
                case 7: // Tìm sinh viên có điểm thấp nhất
                    danhSach.timMin();
                    break;
                case 8: { // Tìm sinh viên theo mã
                    string ma;
                    cout << "Nhập mã sinh viên cần tìm: ";
                    cin >> ma;
                    danhSach.timSinhVien(ma);
                    break;
                }
                case 9: { // Xóa sinh viên theo mã
                    string ma;
                    cout << "Nhập mã sinh viên cần xóa: ";
                    cin >> ma;
                    danhSach.xoaSinhVien(ma);
                    break;
                }
                case 10: // Thêm sinh viên
                    danhSach.themSinhVien();
                    break;
                case 0: // Thoát
                    cout << "Thoát chương trình." << endl;
                    break;
                default:
                    cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại." << endl;
            }
        } while (choice != 0);
    }
};

int main() {
    App app;
    app.hienThiMenu();
    return 0;
}