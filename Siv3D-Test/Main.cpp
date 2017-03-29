﻿
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		if (KeyQ.down())
		{
			if (System::ShowMessageBox(L"アプリを終了します。", MessageBoxButtons::OKCancel)
				== MessageBoxSelection::OK)
			{
				break;
			}
		}
	}
}
