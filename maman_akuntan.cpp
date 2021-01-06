#include <iostream>  //
#include <stdio.h>	 //
#include <stdlib.h>	 //untuk fungsi command yang berkaitan dengan CMD (command prompt) seperti "cls"
#include <conio.h>	 //untuk fungsi Sleep()
#include <windows.h> //untuk fungsi Sleep()
#include <sstream>	 //untuk fungsi string stream pada pembuatan format rupiah di func formatAngka()
#include <string.h>	 //untuk menambahkan fungsi untuk string seperti c_str()
#include <fstream>	 //untuk keperluan read/write file
#include <ctime>	 //untuk keperluan tanggal
using namespace std;

ofstream MyFile; //tipe data ini mewakili aliran file output dan digunakan untuk membuat file dan menulis informasi ke file.
int uangBulanan = 0, hargaMakanMurah = 6500, hargaMakanFav,
	hargaMakanTotal, uangSisa, porsiMakanMurah = 60, porsiMakanFav, slsh, uangMknFav,
	uangMknBiasa;
float jarak = 0;
char pilihan;

void tanggal(string *skrg, string *jam) //Syifa
{
	char buffer[10];
	// current date/time based on current system
	time_t now = time(0);	   //time dengan satuan detik dari 1900  ke sekarang dengan GMT
	tm *ltm = localtime(&now); //menjadikan GMT ke localtime

	// print various components of tm structure.
	int day = ltm->tm_mday;
	int mon = 1 + ltm->tm_mon;
	int year = 1900 + ltm->tm_year;
	int hour = ltm->tm_hour;
	int min = ltm->tm_min;

	string tanggal = itoa(day, buffer, 10); //mengubah interger ke bentuk ascii desimal
	string bulan = itoa(mon, buffer, 10);
	string tahun = itoa(year, buffer, 10);
	string hour_tmp = itoa(hour, buffer, 10);
	string min_tmp = itoa(min, buffer, 10);

	string sekarang_tmp = tanggal + "-" + bulan + "-" + tahun; //18-06-2002
	string jam_tmp = hour_tmp + ":" + min_tmp; //18:00
	*skrg = sekarang_tmp;
	*jam = jam_tmp;
}

void tanggalSelisih(string *tanggal, string *bulan, string *tahun, int *selisih) //syifa
{
	char buffer[10];
	time_t now = time(0);

	tm *ltm = localtime(&now);

	// print various components of tm structure.
	int day, mon, year, i = 0;

	while (day != 1)
	{
		i++;
		int tglSelisih = 60 * 60 * 24 * i; //Merubah hari ke satuan detik
		time_t now = time(0) + tglSelisih; //Menambahkan satuan detik hari yang akan datang ke waktu sekarang
		tm *ltm = localtime(&now);		   //Mencari tanggal dari variable "now" dimana itu adalah mencari selisih tanggal ke akhir bulan
		day = ltm->tm_mday;	//29,30,31,1			   //Menjadikan satuan detik ke tanggal
		mon = 1 + ltm->tm_mon;	//jan,feb		   //Menjadikan satuan detik ke bulan
		year = 1900 + ltm->tm_year;	//2021	   //Menjadikan satuan detik ke tahun
	}

	*selisih = i;					  //tanda "*" adalah menandai variable return menggunakan address
	*tanggal = itoa(day, buffer, 10); //itoa adalah fungsi dari int to ascii dimana merubah interger ke string
	*bulan = itoa(mon, buffer, 10);
	*tahun = itoa(year, buffer, 10);
}

string formatAngka(int angka, string perantara = ".") //syifa //formatAngka(seribu)
{
	stringstream ss;				   //typedata stringstream untuk merecord data yang masuk
	ss << angka;					   //value dari variable angka
	string output = ss.str();		   //fungsi "str()" merubah value dari streamstring ke string
	int inspost = output.length() - 3; //"length()" menghitung banyaknya baris string dengan keluaran int ... 1.000
	while (inspost > 0)				   //berulang hingga keadaan false
	{
		output.insert(inspost, perantara); //meletakan value dari variable perantara ke baris ke 3 (inspost)
		inspost -= 3;					   //mengurangi 3 baris dari value inspost, ini yang akan menjadikan keadaan berulang
	}
	return output; //mengembalikan  nilai output yang sudah di insert value dari variable perantara //1.000
}

void funcFile(string file, string jam) //funcFike(file,jam)
{
	ifstream lihatFile;
	lihatFile.open(file.c_str());//5-1-2021
	MyFile.open(file.c_str(), ios_base::app); //membuka file tanggal sekarang 
	if (!lihatFile)							  //kondisi jika  file tidak ada
	{
		cout << "File tidak ditemukan\n";
		cout << "Membuat file baru\n";
		cout << "Menunggu proses pembuatan file baru...";
		Sleep(1000);
		system("cls");
		ofstream MyFile(file.c_str(), ios_base::app); //maka akan membuat file pada tanggal sekarang
		MyFile << "*****************" << endl;
		MyFile << "* Jam " + jam + " WIB *" << endl;
		MyFile << "*****************" << endl;
	}
	else
	{
		cout << "File sudah ada , apakah akan menulis ulang? Jika iya, file lama akan hilang" << endl;
		cout << "(Y/T) : ";
		char pilihan_tmp;
		cin >> pilihan_tmp;
		if (pilihan_tmp == 'y')
		{
			ofstream MyFile(file.c_str());
			MyFile << "*****************" << endl;
			MyFile << "* Jam " + jam + " WIB *" << endl;
			MyFile << "*****************" << endl;
			cout << "Anda akan lanjut ke halaman utama >>>";
			Sleep(3000);
			system("cls");
		}
		else
		{
			MyFile << "*****************" << endl;
			MyFile << "* Jam " + jam + " WIB *" << endl;
			MyFile << "*****************" << endl;

			cout << "Anda akan lanjut ke halaman yang dipilih >>>";
			Sleep(3000);
			system("cls");
		}
	}
}

void planKendaraan(int uangBulanan, int jarak, int *uangSisa, int hari = 30)
{
	int jmlMinggu;
	float hitungBensin, hargaBensin;
	string kendaraan;
	jmlMinggu = hari / 7;
	cout << "Harga bensin yang kamu pakai sekarang = ";
	cin >> hargaBensin;
nitih1:
	cout << "Motor / Mobil = ";
	cin >> kendaraan;
	if (kendaraan == "Motor" || kendaraan == "motor")
	{

		// menulis ke file
		MyFile << "Info: Anda mengendarai motor dengan 1L BBM = 50KM\n";
		MyFile << "Jarak kampus anda adalah " << jarak << "KM.\n";
		hitungBensin = (jarak * 2 * (hari - jmlMinggu)) / 50;
		MyFile << "Anda membutuhkan bensin " << hitungBensin << "L untuk PP 1 bulan\n";
		hitungBensin *= hargaBensin;
		MyFile << "Jadi uang bensin yang diperlukan adalah Rp" << formatAngka(hitungBensin) << "/Bulan\n";
		if (uangBulanan >= hitungBensin)
		{
			uangBulanan -= hitungBensin;
			MyFile << "Maka uang sisa anda adalah Rp" << formatAngka(uangBulanan) << endl;
			MyFile << "===========================================================================" << endl
				   << endl;
		}
		else if (uangBulanan <= hitungBensin)
		{
			uangBulanan -= hitungBensin;
			MyFile << "Uang bulanan anda tidak cukup untuk membeli bensin selama 1bulan PP kampus.\nAnda harus menambah Rp" << formatAngka(uangBulanan * -1) << endl;
			MyFile << "===========================================================================" << endl
				   << endl;
		}
		*uangSisa = uangBulanan;
	}
	else if (kendaraan == "Mobil" || kendaraan == "mobil")
	{

		// menulis ke file
		MyFile << "Info: Anda mengendarai motor dengan 1L BBM = 15KM\n";
		MyFile << "Jarak kampus anda adalah " << jarak << "KM.\n";
		hitungBensin = jarak * 2 * hari / 15;
		MyFile << "Anda membutuhkan bensin " << hitungBensin << "L untuk PP kampus 1bulan\n";
		hitungBensin *= hargaBensin;
		MyFile << "Jadi uang bensin yang diperlukan adalah Rp" << formatAngka(hitungBensin) << "/Bulan\n";
		uangBulanan -= hitungBensin;
		if (uangBulanan >= hitungBensin)
		{
			MyFile << "Maka uang sisa anda adalah Rp" << formatAngka(uangBulanan) << endl;
			MyFile << "===========================================================================" << endl
				   << endl;
		}
		else if (uangBulanan <= hitungBensin)
		{
			MyFile << "Uang bulanan anda tidak cukup untuk membeli bensin selama 1bulan PP kampus.\nAnda harus menambah Rp" << formatAngka(uangBulanan * -1) << endl;
			MyFile << "===========================================================================" << endl
				   << endl;
		}
		*uangSisa = uangBulanan;
	}
	else
	{
		cout << "Maaf kendaraan yang anda inputkan salah.Silahkan coba lagi.\n\n";
		goto nitih1;
	}
}

int menabungEmas(int uangSisa)
{
	int jml = 0, perbln = uangSisa, tot = 0;
	float bga = 0;

	uangSisa *= 0.017500803198515; //Spread pembelian dan penjualan
	int i = 1;
	MyFile << "\t\t\t\t=====Perkiraan Jika Investasi Emas=====" << endl;

	while (i <= 12)
	{
		MyFile << "Tabungan Bulan ke- " << i;
		bga = (jml + (perbln - (perbln * 0.017500803198515))) * 0.00625; //0.00625 bunga perbulan , 0.0175 spread pembelian dan penjualan
		MyFile << "      bunga : Rp" << formatAngka(bga);				 //tampil bunga
		jml = (jml + perbln) + bga;										 //uang=uang+bunga
		i++;															 ///kenaikan

		MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
	}
	MyFile << "---------------------------------------------------------------------------" << endl;
	tot = jml;
	MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
	MyFile << endl;
}

int menabungReksaDana(int uangSisa)
{
	int jml = 0, perbln = uangSisa, tot = 0;
	float bga = 0;

	int i = 1;
	MyFile << "\t\t\t\t=====Perkiraan Jika Investasi Reksa Dana=====" << endl;

	while (i <= 12)
	{
		MyFile << "Tabungan Bulan ke- " << i;
		bga = (jml + perbln) * 0.008;					  //0.008 bunga perbulan
		MyFile << "      bunga : Rp" << formatAngka(bga); //tampil bunga
		jml = (jml + perbln) + bga;						  //uang=uang+bunga
		i++;											  ///kenaikan

		MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
	}
	MyFile << "---------------------------------------------------------------------------" << endl;
	tot = jml;
	MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
	MyFile << endl;
}

int menabungSaham(int uangSisa)
{
	int jml = 0, perbln = uangSisa, tot = 0;
	float bga = 0;

	int i = 1;
	MyFile << "\t\t\t\t=====Perkiraan Jika Investasi Saham=====" << endl;

	while (i <= 12)
	{
		MyFile << "Tabungan Bulan ke- " << i;
		bga = (jml + perbln) * 0.01667;					  //0.008 bunga perbulan
		MyFile << "      bunga : Rp" << formatAngka(bga); //tampil bunga
		jml = (jml + perbln) + bga;						  //uang=uang+bunga
		i++;											  ///kenaikan

		MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
	}
	MyFile << "---------------------------------------------------------------------------" << endl;
	tot = jml;
	MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
	MyFile << endl;
}

void funcMenabung(int uangDiTabung){
	menabungEmas(uangDiTabung);
		MyFile << endl;
		if (uangDiTabung >= 100000)
		{
			menabungReksaDana(uangDiTabung);
			MyFile << endl;
		}
		else
		{
			MyFile << "Uang sisa kamu tidak bisa untuk menabung Reksadana (Minimal Rp100.000)" << endl;
		}

		if (uangDiTabung >= 200000)
		{
			menabungSaham(uangDiTabung);
			MyFile << endl;
			MyFile << "===========================================================================" << endl
				   << endl;
		}
		else
		{
			MyFile << "Uang sisa kamu tidak bisa untuk menabung Saham (Minimal Rp200.000)" << endl;
		}
		MyFile << "===========================================================================" << endl
			   << endl;
}

void funcPlanning(string h, string b, string t, int slsh, string file, string skrg)
{

	if (pilihan == '1') //plann 1bulan
	{
		slsh = 30;
	pilihan1:
		cout << "Tanggal : " << skrg << endl;
		cout << "Kamu Berada Di Menu -> Plan 1 Bulan" << endl
			 << endl;
		Sleep(1000);

		// Planning Transportasi
		cout << "Input uang saku bulanan = ";
		cin >> uangBulanan;
		cout << "Apakah benar uang bulanan anda sebesar Rp" << formatAngka(uangBulanan) << " ?" ;
		cout << "(Y/T) = ";
		cin >> pilihan;
		if (pilihan == 'T' || pilihan == 't')
		{
			cout << "Silahkan input kembali uang bulanan anda dengan benar!" << endl;
			Sleep(1500);
			system("cls");
			goto pilihan1;
		}
	}
	else if (pilihan == '2')
	{
	pilihan2:
		cout << "Kamu Berada Di Menu -> Plan Darurat" << endl
			 << "Harus bertahan selama -> " << slsh << "-hari, menuju "
			 << h << "-" << b << "-" << t
			 << endl
			 << endl;
		Sleep(1000);

		// Planning Transportasi
		cout << "Input uang saku saat ini = ";
		cin >> uangBulanan;
		cout << "Apakah benar uang bulanan anda sebesar Rp" << formatAngka(uangBulanan) << " ?" << endl;
		cout << "(Y/T) = ";
		cin >> pilihan;
		if (pilihan == 'T' || pilihan == 't')
		{
			cout << "Silahkan input kembali uang bulanan anda dengan benar!" << endl;
			Sleep(1500);
			system("cls");
			goto pilihan2;
		}
	}

	cout << "Input jarak tempat tinggal ke kampus (KM) = ";
	cin >> jarak;
	cout << "Apakah anda mengendarai kendaraan bermotor ke kampus? (Y/T) = ";
	cin >> pilihan;
	if (pilihan == 'Y' || pilihan == 'y')
	{
		planKendaraan(uangBulanan, jarak, &uangSisa, slsh);
	}
	else
	{
		cout << "Kamu bebas uang BBM\n";
	}
	if (uangSisa > 0)
	{
		cout << "Anda akan lanjut ke halaman planing makanan >>>";
		Sleep(3000);
		system("cls");

		// Planning Makanan
		cout << "Tanggal : " << skrg << endl;
		cout << "Harga menu termurah = ";
		cin >> hargaMakanMurah;
		cout << "Harga menu favorite = ";
		cin >> hargaMakanFav;
		cout << "Mau berapa kali memakan makanan favorite? = ";
		cin >> porsiMakanFav;
		if (hargaMakanMurah * (porsiMakanMurah = slsh * 2) <= uangSisa)
		{
			MyFile << "_____________________________________________________________________________\n";
			MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
			MyFile << "|Anda dapat makan sederhana (pagi & malam) sampai akhir bulan dengan tenang.|\n";
			uangMknBiasa = uangSisa - hargaMakanMurah * porsiMakanMurah;
			MyFile << "|Dengan uang sisa Rp" << formatAngka(uangMknBiasa) << "\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
			MyFile << "|___________________________________________________________________________|\n";
			funcMenabung(uangMknBiasa);

			if (hargaMakanMurah * (porsiMakanMurah - porsiMakanFav) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				porsiMakanMurah -= porsiMakanFav;
				MyFile << "_________________________________________________________________\n";
				MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
				MyFile << "|Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\t|\n";
				uangMknFav = uangSisa - ((hargaMakanMurah * porsiMakanMurah) + (hargaMakanFav * porsiMakanFav));
				MyFile << "|Dengan uang sisa Rp" << formatAngka(uangMknFav) << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				MyFile << "|_______________________________________________________________|\n";
				funcMenabung(uangMknFav);
			}
			else if (hargaMakanMurah * (porsiMakanMurah - (porsiMakanFav = 1)) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				while ((hargaMakanMurah * (porsiMakanMurah - porsiMakanFav)) + (hargaMakanFav * porsiMakanFav) <= uangSisa)
				{
					porsiMakanFav++;
				}
				porsiMakanFav -= 1;
				uangMknFav = uangSisa - ((hargaMakanMurah * (porsiMakanMurah -= porsiMakanFav)) + (hargaMakanFav * porsiMakanFav));
				//uangSisa -= (hargaMakanMurah * (porsiMakanMurah -= porsiMakanFav)) + (hargaMakanFav * porsiMakanFav);
				MyFile << "_________________________________________________________________\n";
				MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
				MyFile << "|Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\t|\n";
				MyFile << "|Dengan uang sisa Rp" << formatAngka(uangMknFav) << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				MyFile << "|_______________________________________________________________|\n";
				funcMenabung(uangMknFav);
			}
			else
			{
				MyFile << "Anda tidak bisa makan favorit";
			}
		}
		else
		{
			MyFile << "Uang anda tidak cukup untuk makan 1 bulan\n";
			MyFile << "Uang sisa Rp" << uangSisa << " Hanya cukup untuk makan sederhana (pagi & malam) selama " << uangSisa / hargaMakanMurah / 2 << " hari" << endl;
			MyFile << "Untuk bisa makan (pagi & malam) 1 bulan, maka harus menambah uang sebanyak Rp" << hargaMakanMurah * 60 - uangSisa << endl;
			MyFile << "Dengan menu makanan harga terendah Rp" << formatAngka(hargaMakanMurah);
		}
		cout << "\nSilahkan cek data output anda di -> " << file << endl;
	}
	else
	{
		MyFile << "Karena uang anda tidak cukup untuk membeli BBM , maka uang anda tidak cukup untuk makan 1 bulan\n";
		MyFile << "Uang anda minus Rp" << formatAngka(uangSisa) << endl;
		MyFile << "Untuk bisa makan (pagi & malam) 1 bulan, dan memenuhi kebutuhan BBM.Maka harus menambah uang sebanyak Rp" << formatAngka(hargaMakanMurah * 60 - uangSisa) << endl;
		MyFile << "Dengan menu makanan harga terendah Rp" << formatAngka(hargaMakanMurah);
		cout << "\nSilahkan cek data output anda di -> " << file << endl;
	}
}

int main()
{
	string skrg, jam, h, b, t;
	tanggal(&skrg, &jam);
	string file = skrg + ".txt";
	system("cls");

menu:
	cout << "Tanggal : " << skrg << endl;
	cout << "=====================" << endl;
	cout << "|===MAMAN AKUNTAN===|" << endl;
	cout << "|====KELOMPOK 8=====|" << endl;
	cout << "|                   |" << endl;
	cout << "|SILAHKAN PILIH MENU|" << endl;
	cout << "|1. Plan 1 Bulan    |" << endl;
	cout << "|2. Plan Darurat    |" << endl;
	cout << "|3. Tutorial        |" << endl;
	cout << "=====================" << endl
		 << endl;
	Sleep(1000);
	cout << "Menu yang dipilih : ";
	cin >> pilihan;

	if (pilihan != '3')
	{
		funcFile(file, jam);
	}

	switch (pilihan)
	{
	case '1':
		funcPlanning(h, b, t, slsh, file, skrg);
		MyFile.close();
		break;
	case '2':
		system("cls");
		tanggalSelisih(&h, &b, &t, &slsh);
		funcPlanning(h, b, t, slsh, file, skrg);
		MyFile.close();
		break;

	case '3':
		system("cls");
		cout << "============================================================================================================================" << endl;
		cout << "|==================================================TUTORIAL================================================================|" << endl;
		cout << "|==========================================================================================================================|" << endl;
		cout << "|Plan 1 bulan                                                                                                              |" << endl;
		cout << "|1. masukan nominal uang saku saat ini untuk 1 bulan                                                                       |" << endl;
		cout << "|2. masukan jarak rumah anda ke kampus                                                                                     |" << endl;
		cout << "|3. apakah anda menggunakan kendaran bermotor pribadi? jika ya lanjut mengisi jika tidak langsung mengisi planing makanan  |" << endl;
		cout << "|4. masukan nominal harga bensin saat ini                                                                                  |" << endl;
		cout << "|5. kendaran bermotor apa yang anda gunakan? mobil atau motor?                                                             |" << endl;
		cout << "|6. masukan harga makanan sederhana termurah yg biasa anda makan                                                           |" << endl;
		cout << "|7. masukan harga makanan terfavorit anda                                                                                  |" << endl;
		cout << "|8. sebutkan berapa kali anda ingin makan makanan tervaforit anda                                                          |" << endl;
		cout << "|9. data bisa di lihat di .txt                                                                                             |" << endl;
		cout << "|==========================================================================================================================|" << endl;
		cout << "|Plan darurat akhir bulan bulan                                                                                            |" << endl;
		cout << "|1. masukan nominal uang saku saat ini untuk 1 bulan                                                                       |" << endl;
		cout << "|2. masukan jarak rumah anda ke kampus                                                                                     |" << endl;
		cout << "|3. apakah anda menggunakan kendaran bermotor pribadi? jika ya lanjut mengisi jika tidak langsung mengisi planing makanan  |" << endl;
		cout << "|4. masukan nominal harga bensin saat ini                                                                                  |" << endl;
		cout << "|5. kendaran bermotor apa yang anda gunakan? mobil atau motor?                                                             |" << endl;
		cout << "|6. masukan harga makanan sederhana termurah yg biasa anda makan                                                           |" << endl;
		cout << "|7. masukan harga makanan terfavorit anda                                                                                  |" << endl;
		cout << "|8. sebutkan berapa kali anda ingin makan makanan tervaforit anda                                                          |" << endl;
		cout << "|9. data bisa di lihat di .txt                                                                                             |" << endl;
		cout << "============================================================================================================================" << endl;

		break;
	}
}