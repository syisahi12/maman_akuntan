#include <iostream>
#include <stdio.h>
#include <stdlib.h>		//untuk fungsi command yang berkaitan dengan CMD (command prompt) seperti "cls"
#include <conio.h>		//untuk fungsi Sleep()
#include <windows.h>	//untuk fungsi Sleep()
#include <sstream>		//untuk fungsi string stream pada pembuatan format rupiah di func formatAngka()
#include <string.h>		//untuk menambahkan fungsi untuk string seperti c_str()
#include <fstream>		//untuk keperluan read/write file
#include <ctime>		//untuk keperluan tanggal
#include <cstdlib>
using namespace std;

ofstream MyFile;									//tipe data ini mewakili aliran file output dan digunakan untuk membuat file dan menulis informasi ke file.

string tanggal()
{
	char buffer [33];
	// current date/time based on current system
	time_t now = time(0);							//time dengan satuan detik dari 1900  ke sekarang dengan GMT
	tm *ltm = localtime(&now);						//menjadikan GMT ke localtime

	// print various components of tm structure.
	int day = ltm->tm_mday;
	int mon = 1 + ltm->tm_mon;
	int year = 1900 + ltm->tm_year;

	string tanggal = itoa(day, buffer, 10);			//mengubah interger ke bentuk ascii desimal
	string bulan = itoa(mon, buffer, 10);
	string tahun = itoa(year, buffer, 10);

	string sekarang = tanggal + "-" + bulan + "-" + tahun;
	return sekarang;
}

void tanggalSelisih(string *tanggal, string *bulan, string *tahun, int *selisih)
{
	char buffer[33];
    time_t now = time(0);

    tm *ltm = localtime(&now);

    // print various components of tm structure.
    int day,mon,year,i = 0;

    while (day != 1)
    {
        i++;
        int tglSelisih = 60*60*24*i;		//Merubah hari ke satuan detik
        time_t now = time(0)+tglSelisih;	//Menambahkan satuan detik hari yang akan datang ke waktu sekarang
        tm *ltm = localtime(&now);			//Mencari tanggal dari variable "now" dimana itu adalah mencari selisih tanggal ke akhir bulan
        day = ltm->tm_mday;					//Menjadikan satuan detik ke tanggal
		mon = 1 + ltm->tm_mon;				//Menjadikan satuan detik ke bulan
    	year = 1900 + ltm->tm_year;			//Menjadikan satuan detik ke tahun
    }

	*selisih = i;							//tanda "*" adalah menandai variable return menggunakan address
    *tanggal = itoa(day, buffer, 10);		//itoa adalah fungsi dari int to ascii dimana merubah interger ke string
	*bulan = itoa(mon, buffer, 10);
    *tahun = itoa(year, buffer, 10);

}


string formatAngka(int angka, string perantara = ".")
{
	stringstream ss;							//typedata stringstream untuk merecord data yang masuk
	ss << angka;								//value dari variable angka
	string output = ss.str();					//fungsi "str()" merubah value dari streamstring ke string
	int inspost = output.length() - 3;			//"length()" menghitung banyaknya baris string dengan keluaran int
	while (inspost > 0)							//berulang hingga keadaan false
	{
		output.insert(inspost, perantara);		//meletakan value dari variable perantara ke baris ke 3 (inspost)
		inspost -= 3;							//mengurangi 3 baris dari value inspost, ini yang akan menjadikan keadaan berulang
	}
	return output;								//mengembalikan  nilai output yang sudah di insert value dari variable perantara
}

void planKendaraan(int uangBulanan,int jarak,int* uangSisa,int hari=30){
			int hitungBensin, hargaBensin,jmlMinggu;
			string kendaraan;
			jmlMinggu = hari/7;
	nitih1:
			cout << "Harga bensin yang kamu pakai sekarang = ";
			cin >> hargaBensin;
			cout << "Motor / Mobil = ";
			cin >> kendaraan;
			if (kendaraan == "Motor" || kendaraan == "motor")
			{

				// menulis ke file
				MyFile << "Info: Anda mengendarai motor dengan 1L BBM = 50KM\n";
				MyFile << "Jarak kampus anda adalah " << jarak << "KM.\n";
				hitungBensin = jarak * 2 * (hari-jmlMinggu) / 50;
				MyFile << "Anda membutuhkan bensin " << hitungBensin << "L untuk PP 1 bulan\n";
				hitungBensin *= hargaBensin;
				MyFile << "Jadi uang bensin yang diperlukan adalah Rp" << formatAngka(hitungBensin) << "/Bulan\n";
				uangBulanan -= hitungBensin;
				MyFile << "Maka uang sisa anda adalah Rp" << formatAngka(uangBulanan) << endl;
				MyFile<<"==========================================================================="<<endl<<endl;
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
				MyFile << formatAngka(uangBulanan) << endl;
				MyFile<<"==========================================================================="<<endl<<endl;
				*uangSisa = uangBulanan;
			}
			else
			{
				cout << "Maaf kendaraan yang anda inputkan salah.Silahkan coba lagi.\n\n";
				goto nitih1;
			}
}

int menabungEmas(int uangSisa){
	int jml=0, perbln=uangSisa,tot=0;
    float bga=0;

	uangSisa*=0.017500803198515;				//Spread pembelian dan penjualan
	int i = 1;
	MyFile<<"\t\t\t\t=====Perkiraan Jika Investasi Emas====="<<endl;
	
    while (i <= 12)
    {
        MyFile << "Tabungan Bulan ke- " << i;
        bga = (jml+(perbln-(perbln*0.017500803198515))) * 0.00625;   //0.00625 bunga perbulan , 0.0175 spread pembelian dan penjualan
        MyFile << "      bunga : Rp" << formatAngka(bga); //tampil bunga
        jml = (jml+perbln) + bga;                    //uang=uang+bunga
        i++;                                ///kenaikan

        MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
    }
    MyFile << "---------------------------------------------------------------------------" << endl;
    tot = jml;
    MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
    MyFile << endl;
}

int menabungReksaDana(int uangSisa){
	int jml=0, perbln=uangSisa,tot=0;
    float bga=0;

	int i = 1;
	MyFile<<"\t\t\t\t=====Perkiraan Jika Investasi Reksa Dana====="<<endl;
	
    while (i <= 12)
    {
        MyFile << "Tabungan Bulan ke- " << i;
        bga = (jml+perbln) * 0.008;   //0.008 bunga perbulan
        MyFile << "      bunga : Rp" << formatAngka(bga); //tampil bunga
        jml = (jml+perbln) + bga;                    //uang=uang+bunga
        i++;                                ///kenaikan

        MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
    }
    MyFile << "---------------------------------------------------------------------------" << endl;
    tot = jml;
    MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
    MyFile << endl;
}

int menabungSaham(int uangSisa){
	int jml=0, perbln=uangSisa,tot=0;
    float bga=0;

	int i = 1;
	MyFile<<"\t\t\t\t=====Perkiraan Jika Investasi Saham====="<<endl;
	
    while (i <= 12)
    {
        MyFile << "Tabungan Bulan ke- " << i;
        bga = (jml+perbln) * 0.01667;   //0.008 bunga perbulan
        MyFile << "      bunga : Rp" << formatAngka(bga); //tampil bunga
        jml = (jml+perbln) + bga;                    //uang=uang+bunga
        i++;                                ///kenaikan

        MyFile << "        Saldo : Rp" << formatAngka(jml) << endl;
    }
    MyFile << "---------------------------------------------------------------------------" << endl;
    tot = jml;
    MyFile << "Jumlah tabungan anda dalam setahun : Rp" << formatAngka(tot); //output jumlah uang
    MyFile << endl;
}

int main()
{
	int uangBulanan = 0, hargaMakanMurah, hargaMakanFav, 
					  hargaMakanTotal, uangSisa, porsiMakanMurah = 60, porsiMakanFav,slsh,uangMknFav,
					  uangMknBiasa;
	float jarak = 0;
	char pilihan;
	string file = tanggal() + ".txt",h,b,t;

	system("cls");

	cout << "Tanggal : " << tanggal() << endl;				//memunculkan tanggal sekarang
	ifstream lihatFile;
	lihatFile.open(file.c_str());
	MyFile.open(file.c_str(), ios_base::app);				//membuka file tanggal sekarang
	if (!lihatFile)											//kondisi jika  file tidak ada
	{
		cout << "File tidak ditemukan\n";
		cout << "Membuat file baru\n";
		cout << "Menunggu proses pembuatan file baru...";
		Sleep(1000);
		system("cls");
		ofstream MyFile(file.c_str(), ios_base::app);		//maka akan membuat file pada tanggal sekarang
	} else {
		cout<<"File sudah ada , apakah akan menulis ulang? Jika iya, file lama akan hilang"<<endl;
		cout<<"(Y/T) : ";
		cin>>pilihan;
		while (pilihan == 'y')
		{
			ofstream MyFile(file.c_str());
			cout << "Anda akan lanjut ke halaman utama >>>";
			Sleep(3000);
			system("cls");
			break;
		}
		if (pilihan=='y')
		{
			goto menu;
		}
		
		cout << "Anda akan lanjut ke halaman utama >>>";
			Sleep(3000);
			system("cls");
	}
	menu:
	cout << "Tanggal : " << tanggal() << endl;
	cout << "=====================" << endl;
	cout << "|===MAMAN AKUNTAN===|" << endl;
	cout << "|====KELOMPOK X=====|" << endl;
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

	switch (pilihan)
	{
	case '1':
		system("cls");
		cout << "Tanggal : " << tanggal() << endl;
		cout << "Kamu Berada Di Menu -> Plan 1 Bulan" << endl
			 << endl;
		Sleep(1000);

		// Planning Transportasi
		cout << "Input uang saku bulanan = ";
		cin >> uangBulanan;
		cout << "Input jarak tempat tinggal ke kampus (KM) = ";
		cin >> jarak;
		cout << "Apakah anda mengendarai kendaraan bermotor ke kampus? (Y/T) = ";
		cin >> pilihan;
		if (pilihan == 'Y' || pilihan == 'y')
		{
			planKendaraan(uangBulanan,jarak,&uangSisa);
		}
		else
		{
			cout << "Kamu bebas uang BBM\n";
		}
		cout << "Anda akan lanjut ke halaman planing makanan >>>";
		Sleep(3000);
		system("cls");

		// Planning Makanan
		cout << "Tanggal : " << tanggal() << endl;
		cout << "Harga menu termurah = ";
		cin >> hargaMakanMurah;
		cout << "Harga menu favorite = ";
		cin >> hargaMakanFav;
		cout << "Mau berapa kali memakan makanan favorite? = ";
		cin >> porsiMakanFav;
		if (hargaMakanMurah * porsiMakanMurah <= uangSisa)
		{
			MyFile << "_____________________________________________________________________________\n";
			MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
			MyFile << "|Anda dapat makan sederhana (pagi & malam) sampai akhir bulan dengan tenang.|\n";
			uangMknBiasa = uangSisa - hargaMakanMurah * porsiMakanMurah;
			MyFile << "|Dengan uang sisa Rp" << uangMknBiasa<<"\t\t\t\t\t\t\t\t\t\t\t\t\t|" << endl;
			MyFile << "|___________________________________________________________________________|\n";
			menabungEmas(uangMknBiasa);
			MyFile <<endl;

			if (uangMknBiasa>=100000)
			{
				menabungReksaDana(uangMknBiasa);
				MyFile<<endl;
			}
			
			if (uangMknBiasa>=200000)
			{
				menabungSaham(uangMknBiasa);
				MyFile<<endl;
				MyFile<<"==========================================================================="<<endl<<endl;
			}
			

			if (hargaMakanMurah * (porsiMakanMurah - porsiMakanFav) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				porsiMakanMurah -= porsiMakanFav;
				MyFile << "_________________________________________________________________\n";
				MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
				MyFile << "|Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\t|\n";
				uangMknFav = uangSisa - ((hargaMakanMurah * porsiMakanMurah) + (hargaMakanFav * porsiMakanFav));
				MyFile << "|Dengan uang sisa Rp" << uangMknFav << "\t\t\t\t\t\t\t\t\t\t|" <<endl;
				MyFile << "|_______________________________________________________________|\n";
			}
			else if (hargaMakanMurah * (porsiMakanMurah - (porsiMakanFav = 1)) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				while ((hargaMakanMurah * (porsiMakanMurah - porsiMakanFav)) + (hargaMakanFav * porsiMakanFav) <= uangSisa)
				{
					porsiMakanFav++;
				}
				porsiMakanFav -= 1;
				uangMknFav = uangSisa - (hargaMakanMurah * (porsiMakanMurah -= porsiMakanFav)) + (hargaMakanFav * porsiMakanFav);
				MyFile << "_________________________________________________________________\n";
				MyFile << "|\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n";
				MyFile << "|Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\t|\n";
				MyFile << "|Dengan uang sisa Rp" << uangMknFav << "\t\t\t\t\t\t\t\t\t\t|" << endl;
				MyFile << "|_______________________________________________________________|\n";
			}
			else
			{
				MyFile << "Anda tidak bisa makan favorit";
			}

			menabungEmas(uangMknFav);
			MyFile<<endl;
			if (uangMknFav>=100000)
			{
				menabungReksaDana(uangMknFav);
				MyFile<<endl;
			}
			
			if (uangMknFav>=200000)
			{
				menabungSaham(uangMknFav);
				MyFile<<endl;
			}
		}
		else
		{
			MyFile << "Uang anda tidak cukup untuk makan 1 bulan\n";
			MyFile << "Uang sisa Rp" << uangSisa << " Hanya cukup untuk makan sederhana (pagi & malam) selama " << uangSisa / hargaMakanMurah / 2 << " hari" << endl;
			MyFile << "Untuk bisa makan (pagi & malam) 1 bulan, maka harus menambah uang sebanyak Rp" << hargaMakanMurah * 60 - uangSisa << endl;
		}
		MyFile.close();
		cout<<"\nSilahkan cek data output anda di -> "<<file<<endl;
		break;
	case '2':
		system("cls");
		tanggalSelisih(&h,&b,&t,&slsh);
		cout << "Kamu Berada Di Menu -> Plan Darurat" << endl
			 << "Harus bertahan selama -> "<<slsh<<"-hari, menuju "
			 <<h<<"-"<<b<<"-"<<t
			 <<endl
			 <<endl;
		Sleep(1000);

		// Planning Transportasi
		cout << "Input uang saku saat ini = ";
		cin >> uangBulanan;
		cout << "Input jarak tempat tinggal ke kampus (KM) = ";
		cin >> jarak;
		cout << "Apakah anda mengendarai kendaraan bermotor ke kampus? (Y/T) = ";
		cin >> pilihan;
		if (pilihan == 'Y' || pilihan == 'y')
		{
		planKendaraan(uangBulanan,jarak,&uangSisa,slsh);
		}
		else
		{
			cout << "Kamu bebas uang BBM\n";
		}
		cout << "Anda akan lanjut ke halaman planing makanan >>>";
		Sleep(3000);
		system("cls");

		// Planning Makanan
		cout << "Harga menu termurah = ";
		cin >> hargaMakanMurah;
		cout << "Harga menu favorite = ";
		cin >> hargaMakanFav;
		cout << "Mau berapa kali memakan makanan favorite? = ";
		cin >> porsiMakanFav;
		if (hargaMakanMurah * (porsiMakanMurah=slsh*2) <= uangSisa)
		{

			MyFile << "Anda dapat makan sederhana (pagi & malam) sampai akhir bulan dengan tenang.\n";
			MyFile << "Dengan uang sisa Rp" << uangSisa - hargaMakanMurah * porsiMakanMurah << endl;
			if (hargaMakanMurah * (porsiMakanMurah - porsiMakanFav) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				porsiMakanMurah -= porsiMakanFav;
				MyFile << "Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\n";
				MyFile << "Dengan uang sisa Rp" << uangSisa - ((hargaMakanMurah * porsiMakanMurah) + (hargaMakanFav * porsiMakanFav)) << endl;
			}
			else if (hargaMakanMurah * (porsiMakanMurah - (porsiMakanFav = 1)) + hargaMakanFav * porsiMakanFav <= uangSisa)
			{
				while ((hargaMakanMurah * (porsiMakanMurah - porsiMakanFav)) + (hargaMakanFav * porsiMakanFav) <= uangSisa)
				{
					porsiMakanFav++;
				}
				porsiMakanFav -= 1;
				uangSisa -= (hargaMakanMurah * (porsiMakanMurah -= porsiMakanFav)) + (hargaMakanFav * porsiMakanFav);
				MyFile << "Atau anda juga bisa makan sederhana " << porsiMakanMurah << "x dan makan favorite " << porsiMakanFav << "x\n";
				MyFile << "Dengan uang sisa Rp" << uangSisa << endl;
			}
			else
			{
				MyFile << "Anda tidak bisa makan favorit";
			}
		}
		else
		{
			MyFile << "Uang anda tidak cukup untuk makan hingga akhir bulan\n";
			MyFile << "Uang sisa Rp" << uangSisa << " Hanya cukup untuk makan sederhana (pagi & malam) selama " << uangSisa / hargaMakanMurah / 2 << " hari" << endl;
			MyFile << "Untuk bisa makan (pagi & malam) hingga akhir bulan, maka harus menambah uang sebanyak Rp" << hargaMakanMurah * (slsh * 2) - uangSisa << endl;
		}
		MyFile.close();
		cout<<"\nSilahkan cek data output anda di -> "<<file<<endl;
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