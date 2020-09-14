#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;
struct PPM
{
	char type[2];
	int width;
	int height;
	int shades;
	long datasize;
	unsigned char Red[150000];
	unsigned char Green[150000];
	unsigned char Blue[150000];
};
struct Menu
{
	int mode;
	int main;
	int rotation;
	int filters;
	int cropper;
	int conversion;
};
void infoScreen();
bool confirmPPM(string filename);
void ignoreWSCom(ifstream &img);
void ignoreBinCom(basic_ifstream<unsigned char> &img);
void readPPM(string filename, PPM &val);
void writePPM(string filename, const PPM &val);
int main()
{
	infoScreen();
	while (true)
	{
		try
		{
			PPM pic;
			Menu m;
			string ni, no;
			bool modeflag, filterflag = 0, rotationflag = 0, writeflag = 0;
			while (true)
			{
				cout << "Enter Input Image Location and its name along with ppm extension: ";
				getline(cin, ni);
				if (confirmPPM(ni) == 1)
				{
					break;
				}
				else
				{
					system("cls");
					cout << "Wrong Extension!" << endl;
				}
			}
			system("cls");
			while (true)
			{
				cout << "Enter Output Image Location and its name along with ppm extension: ";
				getline(cin, no);
				if (confirmPPM(no) == 1)
				{
					break;
				}
				else
				{
					system("cls");
					cout << "Wrong Extension!" << endl;
				}
			}
			system("cls");
			while (true)
			{
				cout << "0.Discontinuous Editing Mode\n1.Continuous Editing Mode\n";
				cout << "Choose required option from above menu: ";
				cin >> m.mode;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<int>::max(), '\n');
					system("cls");
					cout << "Invalid Input!" << endl;
					continue;
				}
				if (m.mode == 0)
				{
					modeflag = 0;
				}
				else if (m.mode == 1)
				{
					modeflag = 1;
				}
				else
				{
					system("cls");
					cout << "Invalid input!" << endl;
					continue;
				}
				break;
			}
			system("cls");
			while (true)
			{
				readPPM(ni, pic);
				PPM newpic = pic;
				cout << "0.Rotation\n1.Filters\n2.Crop\n3.Conversion\n4.Exit\n";
				cout << "Choose required option from above menu: ";
				cin >> m.main;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<int>::max(), '\n');
					system("cls");
					cout << "Invalid Input!" << endl;
					continue;
				}
				system("cls");
				if (m.main == 0)
				{
					if (rotationflag == 0)
					{
						int k;
						while (true)
						{
							cout << "0.90 Degree\n1.180 Degree\n2.270 Degree\n3.360 Degree\n";
							cout << "Choose required option from above menu: ";
							cin >> m.rotation;
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<int>::max(), '\n');
								system("cls");
								cout << "Invalid Input!" << endl;
								continue;
							}
							if (m.rotation == 0)
							{
								k = 0;
								for (long j = 0; j < pic.width; j++)
								{
									for (long i = 1; i <= pic.height; i++)
									{
										newpic.Red[k] = pic.Red[pic.width * i - j];
										newpic.Green[k] = pic.Green[pic.width * i - j];
										newpic.Blue[k] = pic.Blue[pic.width * i - j];
										k++;
									}
								}
							}
							else if (m.rotation == 1)
							{
								k = pic.datasize - 1;
								for (long i = 0; i < pic.datasize; i++)
								{
									newpic.Red[i] = pic.Red[k];
									newpic.Green[i] = pic.Green[k];
									newpic.Blue[i] = pic.Blue[k];
									k--;
								}
							}
							else if (m.rotation == 2)
							{
								k = pic.datasize - 1;
								for (long j = 0; j < pic.width; j++)
								{
									for (long i = 1; i <= pic.height; i++)
									{
										newpic.Red[k] = pic.Red[pic.width * i - j];
										newpic.Green[k] = pic.Green[pic.width * i - j];
										newpic.Blue[k] = pic.Blue[pic.width * i - j];
										k--;
									}
								}
							}
							else if (m.rotation == 3)
							{
								newpic = pic;
							}
							else
							{
								system("cls");
								cout << "Invalid input!" << endl;
								continue;
							}
							break;
						}
					}
					else
					{
						cout << "Warning: You can't this feature after cropping, it can harm your image!" << endl;
						system("pause");
						system("cls");
						continue;
					}
				}
				else if (m.main == 1)
				{
					if (filterflag == 0)
					{
						while (true)
						{
							cout << "0.Normal\n1.Black & White\n2.Punch\n3.Bluish\n4.Bleach\n5.X Process\n6.Vintage\n7.Negative\n8.Litho\n9.LightGreen & Pink\n10.Red & LightBlue\n11.Yellow & Blue\n12.SeaGreen & Red\n13.DarkBlue & Yellow\n14.Pink & Green\n15.SeaGreen\n16.Blue\n17.Green\n18.Red\n19.Yellow\n20.Pink\n";
							cout << "Choose required option from above menu: ";
							cin >> m.filters;
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<int>::max(), '\n');
								system("cls");
								cout << "Invalid Input!" << endl;
								continue;
							}
							if (m.filters >= 0 && m.filters <= 20)
							{
								for (long i = 0; i < pic.datasize; i++)
								{
									if (m.filters == 0)
									{
										newpic = pic;
									}
									if (m.filters == 7)
									{
										newpic.Red[i] = pic.shades - pic.Red[i];
										newpic.Green[i] = pic.shades - pic.Green[i];
										newpic.Blue[i] = pic.shades - pic.Blue[i];
									}
									if (m.filters == 1 || m.filters == 4 || m.filters == 6)
									{
										newpic.Red[i] = (pic.Red[i] + pic.Green[i] + pic.Blue[i]) / 3;
									}
									if (m.filters == 1 || m.filters == 2 || m.filters == 5 || m.filters == 6)
									{
										newpic.Green[i] = (pic.Red[i] + pic.Green[i] + pic.Blue[i]) / 3;
									}
									if (m.filters == 1 || m.filters == 2 || m.filters == 3)
									{
										newpic.Blue[i] = (pic.Red[i] + pic.Green[i] + pic.Blue[i]) / 3;
									}
									if (m.filters == 13 || m.filters == 9 || m.filters == 12)
									{
										newpic.Red[i] = i % pic.width;
									}
									if (m.filters == 13 || m.filters == 14 || m.filters == 10)
									{
										newpic.Green[i] = i % pic.width;
									}
									if (m.filters == 9 || m.filters == 10 || m.filters == 11)
									{
										newpic.Blue[i] = i % pic.width;
									}
									if (m.filters == 15 || m.filters == 16 || m.filters == 17)
									{
										newpic.Red[i] = 0;
									}
									if (m.filters == 20 || m.filters == 16 || m.filters == 18)
									{
										newpic.Green[i] = 0;
									}
									if (m.filters == 19 || m.filters == 17 || m.filters == 18)
									{
										newpic.Blue[i] = 0;
									}
								}
								if (modeflag == 1)
								{
									filterflag = 1;
								}
							}
							else
							{
								system("cls");
								cout << "Invalid input!" << endl;
								writeflag = 1;
								continue;
							}
							break;
						}
					}
					else
					{
						cout << "Warning: You can't this feature twice, it can harm your image!" << endl;
						system("pause");
						system("cls");
						continue;
					}
				}
				else if (m.main == 2)
				{
					if (modeflag == 1)
					{
						rotationflag = 1;
					}
					while (true)
					{
						cout << "Enter percentage of unwanted image part: ";
						cin >> m.cropper;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<int>::max(), '\n');
							system("cls");
							cout << "Invalid Input!" << endl;
							continue;
						}
						if (m.cropper >= 0 && m.cropper <= 100)
						{
							newpic.height = pic.height - pic.height * m.cropper / 100;
						}
						else
						{
							system("cls");
							cout << "Invalid input!" << endl;
							continue;
						}
						break;
					}
				}
				else if (m.main == 3)
				{
					while (true)
					{
						cout << "0.Convert to Plain(P3) PPM\n1.Convert to Modern(P6) PPM\n";
						cout << "Choose required option from above menu: ";
						cin >> m.conversion;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<int>::max(), '\n');
							system("cls");
							cout << "Invalid Input!" << endl;
							continue;
						}
						if (m.conversion == 0)
						{
							newpic.type[1] = '3';
						}
						else if (m.conversion == 1)
						{
							newpic.type[1] = '6';
						}
						else
						{
							system("cls");
							cout << "Invalid input!" << endl;
							continue;
						}
						break;
					}
				}
				else if (m.main == 4)
				{
					break;
				}
				else
				{
					system("cls");
					cout << "Invalid input!" << endl;
					continue;
				}
				if (writeflag == 0)
				{
					cout << "Converting ........." << endl;
					writePPM(no, newpic);
					cout << "Conversion completed" << endl;
				}
				writeflag == 0;
				system("cls");
				if (modeflag == 1)
				{
					ni = no;
				}
			}
			break;
		}
		catch (int x)
		{
			char exp;
			cout << "If you want to Exit Press \"E\" or \"e\"\nOtherwise, Press any character to Re-enter filename;\n";
			cin >> exp;
			if (exp == 'E')
			{
				break;
			}
			else
			{
				cin.ignore(1);
				system("cls");
			}
		}
	}
	return EXIT_SUCCESS;
}
void infoScreen()
{
	cout << "\t\t\t\t\t****  *****    *      ***  ****" << endl;
	cout << "\t\t\t\t\t*   * *        *     *   * *   *" << endl;
	cout << "\t\t\t\t\t*   * *        *     *   * *   *" << endl;
	cout << "\t\t\t\t\t****  ****  ** *     ***** **** " << endl;
	cout << "\t\t\t\t\t*     *        *     *   * *   *" << endl;
	cout << "\t\t\t\t\t*     *        *     *   * *   *" << endl;
	cout << "\t\t\t\t\t*     *        ***** *   * ****" << endl;
	cout << "\t **** *****  *   *  *****  **** ***** ***** ****    ****  ****   ***  ***** *****  **** *****" << endl;
	cout << "\t*     *     * * * * *     *       *   *     *   *   *   * *   * *   *   *   *     *       *" << endl;
	cout << "\t*     *     * * * * *     *       *   *     *   *   *   * *   * *   *   *   *     *       *" << endl;
	cout << "\t ***  ****  * * * * ****   ***    *   ****  ****    ****  ****  *   *   *   ****  *       *" << endl;
	cout << "\t    * *     * * * * *         *   *   *     *   *   *     *   * *   * * *   *     *       *" << endl;
	cout << "\t    * *     * * * * *         *   *   *     *   *   *     *   * *   * * *   *     *       *" << endl;
	cout << "\t****  ***** *  *  * ***** ****    *   ***** *   *   *     *   *  ***   *    *****  ****   *" << endl;
	cout << "\n\n" << endl;
	cout << " \t  ****  ****   *   *    ****  *   *   ***  *****  ***    ***** ****  ***** *****  ***  **** " << endl;
	cout << " \t  *   * *   * * * * *   *   * *   *  *   *   *   *   *   *     *   *   *     *   *   * *   *" << endl;
	cout << " \t  *   * *   * * * * *   *   * *   *  *   *   *   *   *   *     *   *   *     *   *   * *   *" << endl;
	cout << " \t  ****  ****  * * * *   ****  *****  *   *   *   *   *   ****  *   *   *     *   *   * ****" << endl;
	cout << " \t  *     *     * * * *   *     *   *  *   *   *   *   *   *     *   *   *     *   *   * *   *" << endl;
	cout << " \t  *     *     * * * *   *     *   *  *   *   *   *   *   *     *   *   *     *   *   * *   *" << endl;
	cout << " \t  *     *     *  *  *   *     *   *   ***    *    ***    ***** ****  *****   *    ***  *   *" << endl;
	cout << "\n\n" << endl;
	cout << "\t\t\t\t\tCreated by Adeel(BCSF17A556)" << endl;
	system("pause");
	system("cls");
}
bool confirmPPM(string filename)
{
	char temp[50];
	strcpy_s(temp, filename.c_str());
	int i = strlen(temp);
	char check[5];
	for (int j = 4; j >= 0; j--)
	{
		check[j] = temp[i];
		i--;
	}
	if (strcmp(check, ".ppm") == 0 || strcmp(check, ".PPM") == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void ignoreWSCom(ifstream &img)
{
	char c;
	while (true)
	{
		img >> ws;
		c = img.peek();
		if (c == '#')
		{
			img.ignore(900000, '\n');
		}
		else if (c >= '0' && c <= '9')
		{
			return;
		}
		else
		{
			img.ignore(1);
		}
	}
}
void ignoreBinCom(basic_ifstream<unsigned char> &img)
{
	unsigned char c;
	while (true)
	{
		c = img.peek();
		if (c == '#')
		{
			img.ignore(900000, '\n');
		}
		else if (c >= '0' && c <= '9')
		{
			return;
		}
	}
}
void readPPM(string filename, PPM &val)
{
	ifstream img(filename.c_str());
	if (img.is_open())
	{
		img >> val.type[0];
		img >> val.type[1];
		if (val.type[1] == '3')
		{
			ignoreWSCom(img);
			img >> val.width;
			ignoreWSCom(img);
			img >> val.height;
			ignoreWSCom(img);
			val.datasize = val.height * val.width;
			img >> val.shades;
			ignoreWSCom(img);
			int temp;
			for (long i = 0; i < val.datasize; i++)
			{
				img >> temp;
				val.Red[i] = temp;
				img >> temp;
				val.Green[i] = temp;
				img >> temp;
				val.Blue[i] = temp;
			}
			img.close();
		}
		else if (val.type[1] == '6')
		{
			ignoreWSCom(img);
			img >> val.width;
			ignoreWSCom(img);
			img >> val.height;
			ignoreWSCom(img);
			val.datasize = val.height * val.width;
			img >> val.shades;
			ignoreWSCom(img);
			img.close();
			basic_ifstream<unsigned char> img(filename.c_str(), ios::binary);
			if (img.is_open())
			{
				img.ignore(3);
				ignoreBinCom(img);
				img.ignore(12, '\n');
				img.ignore(6, '\n');
				/*unsigned char *b = (unsigned char*)malloc(sizeof(unsigned char));*/
				unsigned char *b;
				b = new unsigned char;
				int temp;
				for (long i = 0; i < val.datasize; i++)
				{
					img.read(reinterpret_cast<unsigned char*>(b), 1);
					temp = *b;
					val.Red[i] = temp;
					img.read(reinterpret_cast<unsigned char*>(b), 1);
					temp = *b;
					val.Green[i] = temp;
					img.read(reinterpret_cast<unsigned char*>(b), 1);
					temp = *b;
					val.Blue[i] = temp;
				}
				img.close();
				/*free(b);*/
				delete b;
			}
			else
			{
				cout << "Error reading file: " << filename << endl;
				throw 3;
			}
		}
		else
		{
			cout << "File is neither P3 nor P6 PPM File" << endl;
			throw 1;
		}
	}
	else
	{
		cout << "Error occured while reading file: " << filename << endl;
		throw 1;
	}
}
void writePPM(string filename, const PPM &val)
{
	if (val.type[1] == '3')
	{
		ofstream img(filename.c_str());
		if (img.is_open())
		{
			img << val.type[0];
			img << val.type[1] << endl;
			img << val.width << endl;
			img << val.height << endl;
			img << val.shades << endl;
			for (long i = 0; i < val.datasize; i++)
			{
				if (i != 0 && i % 15 == 0)
				{
					img << endl;
				}
				img << int(val.Red[i]) << " " << int(val.Green[i]) << " " << int(val.Blue[i]) << " ";
			}
			img.close();
		}
		else
		{
			cout << "Error occured while writing file: " << filename << endl;
			throw 1;
		}
	}
	else if (val.type[1] == '6')
	{
		ofstream img(filename.c_str(), ios::binary);
		if (img.is_open())
		{
			img << val.type[0];
			img << val.type[1] << endl;
			img << val.width << " " << val.height << endl;
			img << val.shades << endl;
			for (long i = 0; i < val.datasize; i++)
			{
				img << val.Red[i] << val.Green[i] << val.Blue[i];
			}
			img.close();
		}
		else
		{
			cout << "Error occured while writing file: " << filename << endl;
			throw 1;
		}
	}
	else
	{
		cout << "File is neither P3 nor P6 PPM File" << endl;
		throw 1;
	}
}