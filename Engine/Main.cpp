#include "MainWindow.h"
#include "Game.h"
#include "EException.h"
#include "raytracer.h"

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR pArgs, INT)
{
	try
	{
		MainWindow wnd(hInst, pArgs);
		try
		{
			Game theGame(wnd);

			/*initiate a black bkg*/
			theGame.begin();
			theGame.end();

			theGame.begin();
			raytracer trace;
			trace.dotrace(&theGame);
			//raytracer raytracer();
			//raytracer().dotrace(theGame); //FIX THIS i want to dereference the pointer in function to be called two layers below in another function.
			theGame.end();



			while (wnd.ProcessMessage())
			{
			//	theGame.Go();
				theGame.loopLogic();
			}
		}
		catch (const EException& e)
		{
			//const std::wstring eMsg = e.GetFullMessage() + L"\n\nException caught at Windows message loop.";
			//wnd.ShowMessageBox(e.GetExceptionType(), eMsg);
		}
		catch (const std::exception& e)
		{
			// need to convert std::exception what() string from narrow to wide string
			//const std::string whatStr(e.what());
			//const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) + L"\n\nException caught at Windows message loop.";
			//wnd.ShowMessageBox(L"Unhandled STL Exception", eMsg);
		}
		catch (...)
		{
			//wnd.ShowMessageBox(L"Unhandled Non-STL Exception", L"\n\nException caught at Windows message loop.");
		}
	}
	catch (const EException& e)
	{
		const std::wstring eMsg = e.GetFullMessage() + L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), e.GetExceptionType().c_str(), MB_OK);
	}
	catch (const std::exception& e)
	{
		// need to convert std::exception what() string from narrow to wide string
		const std::string whatStr(e.what());
		const std::wstring eMsg = std::wstring(whatStr.begin(), whatStr.end()) + L"\n\nException caught at main window creation.";
		MessageBox(nullptr, eMsg.c_str(), L"Unhandled STL Exception", MB_OK);
	}
	catch (...)
	{
		MessageBox(nullptr, L"\n\nException caught at main window creation.", L"Unhandled Non-STL Exception", MB_OK);
	}

	return 0;
}