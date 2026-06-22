#include <iostream>             // Input dan output standar
#include <string>               // Tipe data string
#include <cstring>              // Fungsi manipulasi string C
#include <cctype>               // Fungsi pengecekan karakter
#include "raylib.h"             // Library grafis Raylib

#define RAYGUI_IMPLEMENTATION   // Implementasi RayGUI
#include "raygui.h"             // Library GUI untuk Raylib

using namespace std;

// ==== HEADER MODUL HASIL PEMECAHAN ====
#include "Pasien.h"             // Data dan struktur pasien
#include "AuthHashTable.h"      // Hash Table autentikasi pengguna
#include "SimpleTicker.h"       // Ticker/pesan berjalan
#include "RSGraph.h"            // Struktur Graph rumah sakit
#include "ActivityStack.h"      // Stack riwayat aktivitas
#include "AdmisiQueue.h"        // Queue proses admisi pasien
#include "WaitingListPQ.h"      // Priority Queue daftar tunggu
#include "AVLTree.h"            // AVL Tree penyimpanan data
#include "Kamar.h"              // Data dan manajemen kamar
#include "AppFont.h"            // Pengaturan font aplikasi

// ==== DEFINISI GLOBAL FONT ====
Font gFont;

// ==== MAIN PROGRAM GUI ====

enum AppScreen { LOGIN_SCREEN, MAIN_SCREEN };   // Enum untuk menentukan layar/halaman aplikasi yang sedang aktif

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);      // Mengatur jendela agar dapat diubah ukurannya

    // Lebar(W) dan Tinggi(H) tampilan jendela
    const int virtualWidth  = 1200;
    const int virtualHeight = 650;

    // Membuat jendela dan menentukan ukuran minimum jendela
    InitWindow(virtualWidth, virtualHeight, "Sistem Antrean Rawat Inap RS");
    SetWindowMinSize(800, 600);

    // Membuat render texture untuk scaling tampilan dan Menghaluskan hasil scaling
    RenderTexture2D target = LoadRenderTexture(virtualWidth, virtualHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

    GuiLoadStyleDefault();                                          // Memuat style default RayGUI
    gFont = LoadFontEx("C:/Windows/Fonts/arialbd.ttf", 32, 0, 250); // Memuat font Arial Bold
    SetTextureFilter(gFont.texture, TEXTURE_FILTER_BILINEAR);       // Menghaluskan tampilan font
    GuiSetFont(gFont);                                              // Mengatur font GUI
    GuiSetStyle(DEFAULT, TEXT_SIZE, 12);                            // Mengatur ukuran teks GUI
    
    // Objek database autentikasi & Menambah akun pengguna (Admin)
    AuthHashTable authDB;
    authDB.insertUser("feby",   "feby123");
    authDB.insertUser("desi",   "desi123");
    authDB.insertUser("khayla", "khayla123");

    AdmisiQueue   admisi;      // Queue admisi pasien
    WaitingListPQ waitingList; // Priority Queue daftar tunggu
    ActivityStack log;         // Stack log aktivitas
    KamarManager  kamar;       // Manajemen kamar
    SimpleTicker  ticker;      // Ticker informasi berjalan
    RSGraph       mapGraph;    // Graph peta rumah sakit

    // Root AVL Tree arsip pasien
    NodeAVL* arsip = NULL;
    int autoID     = 1;
    AppScreen currentScreen = LOGIN_SCREEN;

    // Input username & password 
    char username[32] = ""; bool userEdit = false;
    char password[32] = ""; bool passEdit = false;
    string loginFeedback = "";  // Pesan hasil login

    // Variabel untuk mengatur pesan dan posisi ticker berjalan
    int    currentMsgIndex  = 0;                                    
    string currentTickerMsg = ticker.getMessage(currentMsgIndex);
    int    tickerX          = virtualWidth;

    // Status popup
    bool showReg      = false;
    bool showCheckout = false;
    bool showDelWL    = false;
    bool showSearch   = false;
    bool showMap      = false;

    // Variabel untuk menyimpan input pengguna dan status pengeditan field
    char nameInput[64] = "";
    char idInput[16]   = "";
    char roomInput[16] = "";
    bool nameEditMode  = false;
    bool idEditMode    = false;
    bool roomEditMode  = false;

    // Variabel untuk menyimpan pilihan menu aktif dan pesan informasi aplikasi
    int    asalActive    = 0;
    int    jaminanActive = 0;
    int    kamarActive   = 0;
    int    mapTarget     = 1;
    string namaErrorMsg       = "";
    string searchResult       = "Nama | Jaminan";
    string checkoutFeedback   = "Menunggu input...";
    string delWlFeedback      = "Menunggu input...";

    SetTargetFPS(60);                   // Mengatur FPS aplikasi menjadi 60

    while (!WindowShouldClose()) {

        // LOGIKA FULLSCREEN
        if (IsKeyPressed(KEY_F11)) {
            if (!IsWindowFullscreen()) {
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
                ToggleFullscreen();
            } else {
                ToggleFullscreen();
                SetWindowSize(virtualWidth, virtualHeight);
            }
        }

        float scale = min((float)GetScreenWidth()  / virtualWidth,
                          (float)GetScreenHeight() / virtualHeight);

        SetMouseOffset(-(GetScreenWidth()  - (virtualWidth  * scale)) * 0.5f,
                       -(GetScreenHeight() - (virtualHeight * scale)) * 0.5f);
        SetMouseScale(1.0f / scale, 1.0f / scale);

        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        // ---- LAYAR LOGIN ----
        if (currentScreen == LOGIN_SCREEN) {
            DrawTextEx(gFont, "PORTAL LOGIN RS", {(float)(virtualWidth / 2 - 100), 200}, 24, 1, BLACK);

            DrawTextEx(gFont, "Username:", {(float)(virtualWidth / 2 - 100), 250}, 12, 1, DARKGRAY);
            if (GuiTextBox((Rectangle){(float)(virtualWidth / 2 - 100), 265, 200, 30},
                           username, 32, userEdit)) userEdit = !userEdit;

            DrawTextEx(gFont, "Password:", {(float)(virtualWidth / 2 - 100), 305}, 12, 1, DARKGRAY);
            if (GuiTextBox((Rectangle){(float)(virtualWidth / 2 - 100), 320, 200, 30},
                           password, 32, passEdit)) passEdit = !passEdit;

            if (GuiButton((Rectangle){(float)(virtualWidth / 2 - 100), 370, 200, 40}, "LOGIN")) {
                if (authDB.authenticate(username, password)) {
                    currentScreen = MAIN_SCREEN;
                } else {
                    loginFeedback = "Username atau Password salah!";
                }
            }

            DrawTextEx(gFont, loginFeedback.c_str(), {(float)(virtualWidth / 2 - 80), 420}, 12, 1, RED);
            DrawTextEx(gFont, "Tekan F11 untuk Full Screen", {10, (float)(virtualHeight - 25)}, 10, 1, GRAY);
        }

        // ---- LAYAR UTAMA ----
        else if (currentScreen == MAIN_SCREEN) {
            DrawTextEx(gFont, "ANTREAN RAWAT INAP RS", {(float)(virtualWidth / 2 - 150), 15}, 24, 1, BLACK);

            if (GuiButton((Rectangle){(float)(virtualWidth - 130), 15, 100, 30}, "LIHAT MAP!"))
                showMap = true;

            GuiGroupBox((Rectangle){20, 50, (float)(virtualWidth - 40), 120}, "STATUS KAMAR RAWAT INAP");
            kamar.drawGUI(35, 70);

            int listY = 185, listH = 320, gap = 20;
            int listW = (virtualWidth - 80) / 3;

            GuiGroupBox((Rectangle){20, (float)listY, (float)listW, (float)listH}, "WAITING LIST");
            waitingList.drawGUI(35, listY + 20);

            GuiGroupBox((Rectangle){20.0f + listW + gap, (float)listY, (float)listW, (float)listH}, "ANTREAN ADMISI");
            admisi.drawGUI(35 + listW + gap, listY + 20);

            GuiGroupBox((Rectangle){20.0f + (listW + gap) * 2, (float)listY, (float)listW, (float)listH}, "LOG AKTIVITAS");
            log.drawGUI(35 + (listW + gap) * 2, listY + 20);

            int btnW = 210, btnH = 40, btnY = 530;
            int btnGap = (virtualWidth - 40 - (btnW * 5)) / 4;
            if (btnGap < 5) btnGap = 5;

            if (!showReg && !showCheckout && !showDelWL && !showSearch && !showMap) {
                if (GuiButton((Rectangle){20, (float)btnY, (float)btnW, (float)btnH}, "REGISTER")) {
                    showReg      = true;
                    namaErrorMsg = "";
                    strcpy(nameInput, "");
                }
                if (GuiButton((Rectangle){20.0f + (btnW + btnGap), (float)btnY, (float)btnW, (float)btnH}, "DELETE WL")) {
                    showDelWL    = true;
                    strcpy(idInput, "");
                    delWlFeedback = "Menunggu input...";
                }
                if (GuiButton((Rectangle){20.0f + (btnW + btnGap) * 2, (float)btnY, (float)btnW, (float)btnH}, "PROCESS")) {
                    if (!admisi.empty()) {
                        Pasien p   = admisi.dequeue();
                        int    idx = kamar.allocateRoom(p.hakKamar);
                        if (idx != -1) {
                            kamar.kamar[idx].terisi = true;
                            kamar.kamar[idx].pasien = p;
                            log.push("Masuk kamar: " + p.nama);
                        } else {
                            waitingList.enqueue(p);
                            log.push("Waiting list: " + p.nama);
                        }
                    }
                }
                if (GuiButton((Rectangle){20.0f + (btnW + btnGap) * 3, (float)btnY, (float)btnW, (float)btnH}, "CHECKOUT")) {
                    showCheckout    = true;
                    strcpy(roomInput, "");
                    checkoutFeedback = "Menunggu input...";
                }
                if (GuiButton((Rectangle){20.0f + (btnW + btnGap) * 4, (float)btnY, (float)btnW, (float)btnH}, "SEARCH")) {
                    showSearch = true;
                    strcpy(idInput, "");
                }
            } else {
                GuiSetState(STATE_DISABLED);
                GuiButton((Rectangle){20, (float)btnY, (float)btnW, (float)btnH}, "REGISTER");
                GuiButton((Rectangle){20.0f + (btnW + btnGap),       (float)btnY, (float)btnW, (float)btnH}, "DELETE WL");
                GuiButton((Rectangle){20.0f + (btnW + btnGap) * 2,   (float)btnY, (float)btnW, (float)btnH}, "PROCESS");
                GuiButton((Rectangle){20.0f + (btnW + btnGap) * 3,   (float)btnY, (float)btnW, (float)btnH}, "CHECKOUT");
                GuiButton((Rectangle){20.0f + (btnW + btnGap) * 4,   (float)btnY, (float)btnW, (float)btnH}, "SEARCH");
                GuiSetState(STATE_NORMAL);
            }

            // Running Text / Ticker
            DrawRectangle(0, virtualHeight - 35, virtualWidth, 35, Fade(DARKGRAY, 0.8f));
            tickerX -= 2;
            if (tickerX < -(int)MeasureTextEx(gFont, currentTickerMsg.c_str(), 14, 1).x) {
                tickerX = virtualWidth;
                currentMsgIndex++;
                currentTickerMsg = ticker.getMessage(currentMsgIndex);
            }
            DrawTextEx(gFont, currentTickerMsg.c_str(), {(float)tickerX, (float)(virtualHeight - 25)}, 14, 1, RAYWHITE);

            // Overlay gelap saat popup aktif
            if (showReg || showCheckout || showDelWL || showSearch || showMap) {
                DrawRectangle(0, 0, virtualWidth, virtualHeight, Fade(BLACK, 0.5f));
            }

            // ---- POPUP SEARCH ----
            if (showSearch) {
                Rectangle popup = {(float)(virtualWidth / 2 - 160), (float)(virtualHeight / 2 - 100), 320, 200};
                DrawRectangleRec(popup, RAYWHITE);
                DrawRectangleLinesEx(popup, 2, DARKGRAY);
                DrawTextEx(gFont, "CARI ARSIP PASIEN", {popup.x + 75, popup.y + 15}, 15, 1, BLACK);

                DrawTextEx(gFont, "ID Pasien:", {popup.x + 20, popup.y + 50}, 12, 1, DARKGRAY);
                if (GuiTextBox((Rectangle){popup.x + 20, popup.y + 65, 280, 30},
                               idInput, 16, idEditMode)) idEditMode = !idEditMode;

                if (GuiButton((Rectangle){popup.x + 20, popup.y + 110, 280, 30}, "SEARCH")) {
                    int id          = atoi(idInput);
                    NodeAVL* result = searchAVL(arsip, id);
                    if (result != NULL) searchResult = result->data.nama + " | " + result->data.jaminan;
                    else                searchResult = "Pasien tidak ditemukan.";
                }
                DrawTextEx(gFont, searchResult.c_str(), {popup.x + 20, popup.y + 155}, 12, 1, DARKGRAY);

                if (GuiButton((Rectangle){popup.x + 295, popup.y + 5, 20, 20}, "X"))
                    showSearch = false;
            }

            // ---- POPUP MAP ----
            if (showMap) {
                Rectangle popup = {(float)(virtualWidth / 2 - 250), (float)(virtualHeight / 2 - 200), 500, 400};
                DrawRectangleRec(popup, RAYWHITE);
                DrawRectangleLinesEx(popup, 2, DARKGRAY);

                DrawTextEx(gFont, "MAP RUANG RAWAT INAP", {popup.x + 150, popup.y + 15}, 15, 1, BLACK);

                DrawTextEx(gFont, "Tujuan dari Lobi:", {popup.x + 20, popup.y + 50}, 12, 1, DARKGRAY);
                GuiToggleGroup((Rectangle){popup.x + 120, popup.y + 40, 60, 30},
                               "Lorong Utama;VIP;Kelas 1;Kelas 2;Kelas 3", &mapTarget);

                mapGraph.doBFS(0, mapTarget + 1);

                Vector2 nodes[6] = {
                    {popup.x + 50,  popup.y + 200},
                    {popup.x + 150, popup.y + 200},
                    {popup.x + 250, popup.y + 120},
                    {popup.x + 250, popup.y + 200},
                    {popup.x + 350, popup.y + 200},
                    {popup.x + 450, popup.y + 200}
                };
                string nName[6] = {"LOBI", "LORONG", "VIP", "KELAS1", "KELAS2", "KELAS3"};

                // Gambar semua edge (abu-abu)
                for (int i = 0; i < 6; i++) {
                    for (int j = i + 1; j < 6; j++) {
                        if ((i==0&&j==1)||(i==1&&j==2)||(i==1&&j==3)||(i==3&&j==4)||(i==4&&j==5)) {
                            DrawLineEx(nodes[i], nodes[j], 3.0f, LIGHTGRAY);
                        }
                    }
                }

                // Gambar jalur hasil BFS (merah)
                int curr = mapTarget + 1;
                while (mapGraph.parent[curr] != -1) {
                    int p = mapGraph.parent[curr];
                    DrawLineEx(nodes[curr], nodes[p], 5.0f, RED);
                    curr = p;
                }

                // Gambar node
                for (int i = 0; i < 6; i++) {
                    Color c = (i == mapTarget + 1 || i == 0) ? MAROON : DARKBLUE;
                    DrawCircleV(nodes[i], 15, c);
                    DrawTextEx(gFont, nName[i].c_str(), {nodes[i].x - 15, nodes[i].y + 20}, 10, 1, BLACK);
                }

                if (GuiButton((Rectangle){popup.x + 475, popup.y + 5, 20, 20}, "X"))
                    showMap = false;
            }

            // ---- POPUP REGISTER ----
            if (showReg) {
                Rectangle popup = {(float)(virtualWidth / 2 - 160), (float)(virtualHeight / 2 - 220), 320, 440};
                DrawRectangleRec(popup, RAYWHITE);
                DrawRectangleLinesEx(popup, 2, DARKGRAY);
                DrawTextEx(gFont, "REGISTRASI PASIEN", {popup.x + 85, popup.y + 15}, 15, 1, BLACK);

                DrawTextEx(gFont, "Nama Pasien:", {popup.x + 20, popup.y + 50}, 12, 1, DARKGRAY);
                if (GuiTextBox((Rectangle){popup.x + 20, popup.y + 65, 280, 30},
                               nameInput, 64, nameEditMode)) nameEditMode = !nameEditMode;

                // Tampilkan pesan error di bawah kotak nama
                if (!namaErrorMsg.empty()) {
                    DrawTextEx(gFont, namaErrorMsg.c_str(), {popup.x + 20, popup.y + 100}, 11, 1, RED);
                }

                DrawTextEx(gFont, "Asal Masuk:", {popup.x + 20, popup.y + 115}, 12, 1, DARKGRAY);
                GuiToggleGroup((Rectangle){popup.x + 20, popup.y + 130, 80, 30}, "IGD;POLI", &asalActive);

                DrawTextEx(gFont, "Jaminan:", {popup.x + 20, popup.y + 180}, 12, 1, DARKGRAY);
                int oldJam = jaminanActive;
                GuiToggleGroup((Rectangle){popup.x + 20, popup.y + 195, 75, 30},
                               "BPJS;UMUM;ASURANSI", &jaminanActive);
                if (oldJam != jaminanActive) kamarActive = 0;

                DrawTextEx(gFont, "Hak Kamar:", {popup.x + 20, popup.y + 245}, 12, 1, DARKGRAY);
                if (jaminanActive == 2)
                    GuiToggleGroup((Rectangle){popup.x + 20, popup.y + 260, 90, 30},
                                   "Standar;Deluxe;VIP", &kamarActive);
                else
                    GuiToggleGroup((Rectangle){popup.x + 20, popup.y + 260, 65, 30},
                                   "VIP;KELAS1;KELAS2;KELAS3", &kamarActive);

                if (GuiButton((Rectangle){popup.x + 20, popup.y + 350, 130, 40}, "SIMPAN")) {
                    string tempNama = nameInput;

                    // ---- VALIDASI NAMA ----
                    bool namaValid = !tempNama.empty();
                    if (namaValid) {
                        // Tidak boleh mengandung angka atau karakter selain huruf dan spasi
                        for (char c : tempNama) {
                            if (!isalpha((unsigned char)c) && c != ' ') {
                                namaValid = false;
                                break;
                            }
                        }
                    }
                    // Tidak boleh hanya spasi saja
                    if (namaValid) {
                        bool adaHuruf = false;
                        for (char c : tempNama) {
                            if (isalpha((unsigned char)c)) { adaHuruf = true; break; }
                        }
                        if (!adaHuruf) namaValid = false;
                    }

                    if (namaValid) {
                        Pasien p;
                        p.id       = autoID++;
                        p.nama     = tempNama;
                        p.asalMasuk = (asalActive == 0) ? "IGD" : "POLI";

                        if      (jaminanActive == 0) p.jaminan = "BPJS";
                        else if (jaminanActive == 1) p.jaminan = "UMUM";
                        else                          p.jaminan = "ASURANSI";

                        if (jaminanActive == 2) {
                            if      (kamarActive == 0) p.hakKamar = "Standar";
                            else if (kamarActive == 1) p.hakKamar = "Deluxe";
                            else                        p.hakKamar = "VIP";
                        } else {
                            if      (kamarActive == 0) p.hakKamar = "VIP";
                            else if (kamarActive == 1) p.hakKamar = "KELAS1";
                            else if (kamarActive == 2) p.hakKamar = "KELAS2";
                            else                        p.hakKamar = "KELAS3";
                        }

                        admisi.enqueue(p);
                        log.push("Registrasi baru: " + p.nama);
                        namaErrorMsg = "";
                        showReg = false;
                    } else {
                        namaErrorMsg = "Nama tidak boleh kosong / mengandung angka!";
                    }
                }
                if (GuiButton((Rectangle){popup.x + 170, popup.y + 350, 130, 40}, "BATAL")) {
                    namaErrorMsg = "";
                    showReg = false;
                }
            }

            // ---- POPUP CHECKOUT ----
            if (showCheckout) {
                Rectangle popup = {(float)(virtualWidth / 2 - 140), (float)(virtualHeight / 2 - 100), 280, 200};
                DrawRectangleRec(popup, RAYWHITE);
                DrawRectangleLinesEx(popup, 2, DARKGRAY);
                DrawTextEx(gFont, "CHECKOUT PASIEN", {popup.x + 70, popup.y + 15}, 15, 1, BLACK);

                DrawTextEx(gFont, "Nomor Kamar:", {popup.x + 20, popup.y + 40}, 12, 1, DARKGRAY);
                if (GuiTextBox((Rectangle){popup.x + 20, popup.y + 55, 240, 30},
                               roomInput, 16, roomEditMode)) roomEditMode = !roomEditMode;

                if (GuiButton((Rectangle){popup.x + 20, popup.y + 100, 240, 35}, "CHECKOUT")) {
                    string no(roomInput);
                    bool found = false;

                    for (int i = 0; i < 8; i++) {
                        if (kamar.kamar[i].nomor == no && kamar.kamar[i].terisi) {
                            Pasien keluar          = kamar.kamar[i].pasien;
                            arsip                  = insertAVL(arsip, keluar);
                            kamar.kamar[i].terisi  = false;

                            log.push("Checkout: " + keluar.nama);
                            checkoutFeedback = "Pasien " + keluar.nama + " keluar ruangan.";

                            Pasien next = waitingList.dequeueSuitable(kamar.kamar[i].tipe);
                            if (next.id != 0) {
                                kamar.kamar[i].pasien = next;
                                kamar.kamar[i].terisi = true;
                                log.push("Masuk kamar dr WL: " + next.nama);
                            }
                            found = true;
                            break;
                        }
                    }
                    if (!found) checkoutFeedback = "Kamar kosong / tidak valid!";
                }
                DrawTextEx(gFont, checkoutFeedback.c_str(), {popup.x + 20, popup.y + 155}, 12, 1, GRAY);

                if (GuiButton((Rectangle){popup.x + 255, popup.y + 5, 20, 20}, "X"))
                    showCheckout = false;
            }

            // ---- POPUP DELETE WAITING LIST ----
            if (showDelWL) {
                Rectangle popup = {(float)(virtualWidth / 2 - 140), (float)(virtualHeight / 2 - 100), 280, 200};
                DrawRectangleRec(popup, RAYWHITE);
                DrawRectangleLinesEx(popup, 2, DARKGRAY);
                DrawTextEx(gFont, "HAPUS WAITING LIST", {popup.x + 60, popup.y + 15}, 15, 1, BLACK);

                DrawTextEx(gFont, "ID Pasien:", {popup.x + 20, popup.y + 40}, 12, 1, DARKGRAY);
                if (GuiTextBox((Rectangle){popup.x + 20, popup.y + 55, 240, 30},
                               idInput, 16, idEditMode)) idEditMode = !idEditMode;

                if (GuiButton((Rectangle){popup.x + 20, popup.y + 100, 240, 35}, "HAPUS")) {
                    int id = atoi(idInput);
                    if (waitingList.removeByID(id)) delWlFeedback = "Berhasil dihapus!";
                    else                             delWlFeedback = "ID tidak ditemukan.";
                }
                DrawTextEx(gFont, delWlFeedback.c_str(), {popup.x + 20, popup.y + 155}, 12, 1, GRAY);

                if (GuiButton((Rectangle){popup.x + 255, popup.y + 5, 20, 20}, "X"))
                    showDelWL = false;
            }
        }

        EndTextureMode();                   // Mengakhiri proses render ke RenderTexture

        BeginDrawing();                     // Memulai proses menggambar ke layar
        ClearBackground(BLACK);             // Membersihkan layar dengan warna hitam

        // Mengatur sumber render texture, posisi tampilan agar terpusat di layar, serta ukuran hasil scaling
        Rectangle sourceRec = {0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height};
        Rectangle destRec   = {
            (GetScreenWidth()  - ((float)virtualWidth  * scale)) * 0.5f,
            (GetScreenHeight() - ((float)virtualHeight * scale)) * 0.5f,
            (float)virtualWidth  * scale,
            (float)virtualHeight * scale
        };

        DrawTexturePro(target.texture, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
        EndDrawing();                        // Mengakhiri proses menggambar frame
    }

    UnloadFont(gFont);                      // Membebaskan memori font yang digunakan
    UnloadRenderTexture(target);            // Membebaskan memori RenderTexture
    CloseWindow();                          // Menutup jendela aplikasi
    return 0;                               // Mengakhiri program dengan status sukses
}