#pragma once
#include "veda.h"
#include <Shlobj.h>
#pragma comment(lib,"Shell32.lib")
namespace veda
{
	class VEDA_EXPORT SpecialFolder
	{
	public:
		// %APPDATA%\Microsoft\Windows\AccountPictures
		REFKNOWNFOLDERID AccountPictures = FOLDERID_AccountPictures;
		// Get Programs
		REFKNOWNFOLDERID AddNewPrograms = FOLDERID_AddNewPrograms;
		// %APPDATA%\Microsoft\Windows\Start Menu\Programs\Administrative Tools
		REFKNOWNFOLDERID AdminTools = FOLDERID_AdminTools;
		// %LOCALAPPDATA%\Microsoft\Windows\Application Shortcuts
		REFKNOWNFOLDERID ApplicationShortcuts = FOLDERID_ApplicationShortcuts;
		// Applications
		REFKNOWNFOLDERID AppsFolder = FOLDERID_AppsFolder;
		// Installed Updates
		REFKNOWNFOLDERID AppUpdates = FOLDERID_AppUpdates;
		// %USERPROFILE%\Pictures\Camera Roll
		REFKNOWNFOLDERID CameraRoll = FOLDERID_CameraRoll;
		// %LOCALAPPDATA%\Microsoft\Windows\Burn\Burn
		REFKNOWNFOLDERID CDBurning = FOLDERID_CDBurning;
		// Programs and Features
		REFKNOWNFOLDERID ChangeRemovePrograms = FOLDERID_ChangeRemovePrograms;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Start Menu\Programs\Administrative Tools
		REFKNOWNFOLDERID CommonAdminTools = FOLDERID_CommonAdminTools;
		// %ALLUSERSPROFILE%\OEM Links
		REFKNOWNFOLDERID CommonOEMLinks = FOLDERID_CommonOEMLinks;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Start Menu\Programs
		REFKNOWNFOLDERID CommonPrograms = FOLDERID_CommonPrograms;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Start Menu
		REFKNOWNFOLDERID CommonStartMenu = FOLDERID_CommonStartMenu;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Start Menu\Programs\StartUp
		REFKNOWNFOLDERID CommonStartup = FOLDERID_CommonStartup;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Templates
		REFKNOWNFOLDERID CommonTemplates = FOLDERID_CommonTemplates;
		// Computer
		REFKNOWNFOLDERID ComputerFolder = FOLDERID_ComputerFolder;
		// Conflicts
		REFKNOWNFOLDERID ConflictFolder = FOLDERID_ConflictFolder;
		// Network Connections
		REFKNOWNFOLDERID ConnectionsFolder = FOLDERID_ConnectionsFolder;
		// %USERPROFILE%\Contacts
		REFKNOWNFOLDERID Contacts = FOLDERID_Contacts;
		// Control Panel
		REFKNOWNFOLDERID ControlPanelFolder = FOLDERID_ControlPanelFolder;
		// %APPDATA%\Microsoft\Windows\Cookies
		REFKNOWNFOLDERID Cookies = FOLDERID_Cookies;
		// %USERPROFILE%\Desktop
		REFKNOWNFOLDERID Desktop = FOLDERID_Desktop;
		// %ALLUSERSPROFILE%\Microsoft\Windows\DeviceMetadataStore
		REFKNOWNFOLDERID DeviceMetadataStore = FOLDERID_DeviceMetadataStore;
		// %USERPROFILE%\Documents
		REFKNOWNFOLDERID Documents = FOLDERID_Documents;
		// %APPDATA%\Microsoft\Windows\Libraries\Documents.library-ms
		REFKNOWNFOLDERID DocumentsLibrary = FOLDERID_DocumentsLibrary;
		// %USERPROFILE%\Downloads
		REFKNOWNFOLDERID Downloads = FOLDERID_Downloads;
		// %USERPROFILE%\Favorites
		REFKNOWNFOLDERID Favorites = FOLDERID_Favorites;
		// %windir%\Fonts
		REFKNOWNFOLDERID Fonts = FOLDERID_Fonts;
		// Games
		REFKNOWNFOLDERID Games = FOLDERID_Games;
		// %LOCALAPPDATA%\Microsoft\Windows\GameExplorer
		REFKNOWNFOLDERID GameTasks = FOLDERID_GameTasks;
		// %LOCALAPPDATA%\Microsoft\Windows\History
		REFKNOWNFOLDERID History = FOLDERID_History;
		// Homegroup
		REFKNOWNFOLDERID HomeGroup = FOLDERID_HomeGroup;
		// The user's username (%USERNAME%)
		REFKNOWNFOLDERID HomeGroupCurrentUser = FOLDERID_HomeGroupCurrentUser;
		// %APPDATA%\Microsoft\Internet Explorer\Quick Launch\User Pinned\ImplicitAppShortcuts
		REFKNOWNFOLDERID ImplicitAppShortcuts = FOLDERID_ImplicitAppShortcuts;
		// %LOCALAPPDATA%\Microsoft\Windows\Temporary Internet Files
		REFKNOWNFOLDERID InternetCache = FOLDERID_InternetCache;
		// The Internet
		REFKNOWNFOLDERID InternetFolder = FOLDERID_InternetFolder;
		// %APPDATA%\Microsoft\Windows\Libraries
		REFKNOWNFOLDERID Libraries = FOLDERID_Libraries;
		// %USERPROFILE%\Links
		REFKNOWNFOLDERID Links = FOLDERID_Links;
		// %LOCALAPPDATA % (%USERPROFILE%\AppData\Local)
		REFKNOWNFOLDERID LocalAppData = FOLDERID_LocalAppData;
		// %USERPROFILE%\AppData\LocalLow
		REFKNOWNFOLDERID LocalAppDataLow = FOLDERID_LocalAppDataLow;
		// %windir%\resources\0409 (code page)
		REFKNOWNFOLDERID LocalizedResourcesDir = FOLDERID_LocalizedResourcesDir;
		// %USERPROFILE%\Music
		REFKNOWNFOLDERID Music = FOLDERID_Music;
		// %APPDATA%\Microsoft\Windows\Libraries\Music.library-ms
		REFKNOWNFOLDERID MusicLibrary = FOLDERID_MusicLibrary;
		// %APPDATA%\Microsoft\Windows\Network Shortcuts
		REFKNOWNFOLDERID NetHood = FOLDERID_NetHood;
		// Network
		REFKNOWNFOLDERID NetworkFolder = FOLDERID_NetworkFolder;
		// %LOCALAPPDATA%\Microsoft\Windows Photo Gallery\Original Images
		REFKNOWNFOLDERID OriginalImages = FOLDERID_OriginalImages;
		// %USERPROFILE%\Pictures\Slide Shows
		REFKNOWNFOLDERID PhotoAlbums = FOLDERID_PhotoAlbums;
		// %APPDATA%\Microsoft\Windows\Libraries\Pictures.library-ms
		REFKNOWNFOLDERID PicturesLibrary = FOLDERID_PicturesLibrary;
		// %USERPROFILE%\Pictures
		REFKNOWNFOLDERID Pictures = FOLDERID_Pictures;
		// %USERPROFILE%\Music\Playlists
		REFKNOWNFOLDERID Playlists = FOLDERID_Playlists;
		// Printers
		REFKNOWNFOLDERID PrintersFolder = FOLDERID_PrintersFolder;
		// %APPDATA%\Microsoft\Windows\Printer Shortcuts
		REFKNOWNFOLDERID PrintHood = FOLDERID_PrintHood;
		// %USERPROFILE% (%SystemDrive%\Users\%USERNAME%)
		REFKNOWNFOLDERID Profile = FOLDERID_Profile;
		// %ALLUSERSPROFILE% (%ProgramData%, %SystemDrive%\ProgramData)
		REFKNOWNFOLDERID ProgramData = FOLDERID_ProgramData;
		// %ProgramFiles% (%SystemDrive%\Program Files)
		REFKNOWNFOLDERID ProgramFiles = FOLDERID_ProgramFiles;
		// %ProgramFiles% (%SystemDrive%\Program Files)
		REFKNOWNFOLDERID ProgramFilesX64 = FOLDERID_ProgramFilesX64;
		// %ProgramFiles% (%SystemDrive%\Program Files)
		REFKNOWNFOLDERID ProgramFilesX86 = FOLDERID_ProgramFilesX86;
		// %ProgramFiles%\Common Files
		REFKNOWNFOLDERID ProgramFilesCommon = FOLDERID_ProgramFilesCommon;
		// %ProgramFiles%\Common Files
		REFKNOWNFOLDERID ProgramFilesCommonX64 = FOLDERID_ProgramFilesCommonX64;
		// %ProgramFiles%\Common Files
		REFKNOWNFOLDERID ProgramFilesCommonX86 = FOLDERID_ProgramFilesCommonX86;
		// %APPDATA%\Microsoft\Windows\Start Menu\Programs
		REFKNOWNFOLDERID Programs = FOLDERID_Programs;
		// %PUBLIC% (%SystemDrive%\Users\Public)
		REFKNOWNFOLDERID Public = FOLDERID_Public;
		// %PUBLIC%\Desktop
		REFKNOWNFOLDERID PublicDesktop = FOLDERID_PublicDesktop;
		// %PUBLIC%\Documents
		REFKNOWNFOLDERID PublicDocuments = FOLDERID_PublicDocuments;
		// %PUBLIC%\Downloads
		REFKNOWNFOLDERID PublicDownloads = FOLDERID_PublicDownloads;
		// %ALLUSERSPROFILE%\Microsoft\Windows\GameExplorer
		REFKNOWNFOLDERID PublicGameTasks = FOLDERID_PublicGameTasks;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Libraries
		REFKNOWNFOLDERID PublicLibraries = FOLDERID_PublicLibraries;
		// %PUBLIC%\Music
		REFKNOWNFOLDERID PublicMusic = FOLDERID_PublicMusic;
		// %PUBLIC%\Pictures
		REFKNOWNFOLDERID PublicPictures = FOLDERID_PublicPictures;
		// %ALLUSERSPROFILE%\Microsoft\Windows\Ringtones
		REFKNOWNFOLDERID PublicRingtones = FOLDERID_PublicRingtones;
		// %PUBLIC%\AccountPictures
		REFKNOWNFOLDERID PublicUserTiles = FOLDERID_PublicUserTiles;
		// %PUBLIC%\Videos
		REFKNOWNFOLDERID PublicVideos = FOLDERID_PublicVideos;
		// %APPDATA%\Microsoft\Internet Explorer\Quick Launch
		REFKNOWNFOLDERID QuickLaunch = FOLDERID_QuickLaunch;
		// %APPDATA%\Microsoft\Windows\Recent
		REFKNOWNFOLDERID Recent = FOLDERID_Recent;
		// %PUBLIC%\RecordedTV.library-ms
		REFKNOWNFOLDERID RecordedTVLibrary = FOLDERID_RecordedTVLibrary;
		// Recycle Bin
		REFKNOWNFOLDERID RecycleBinFolder = FOLDERID_RecycleBinFolder;
		// %windir%\Resources
		REFKNOWNFOLDERID ResourceDir = FOLDERID_ResourceDir;
		// %LOCALAPPDATA%\Microsoft\Windows\Ringtones
		REFKNOWNFOLDERID Ringtones = FOLDERID_Ringtones;
		// %APPDATA% (%USERPROFILE%\AppData\Roaming)
		REFKNOWNFOLDERID RoamingAppData = FOLDERID_RoamingAppData;
		// %LOCALAPPDATA%\Microsoft\Windows\RoamedTileImages
		REFKNOWNFOLDERID RoamedTileImages = FOLDERID_RoamedTileImages;
		// %LOCALAPPDATA%\Microsoft\Windows\RoamingTiles
		REFKNOWNFOLDERID RoamingTiles = FOLDERID_RoamingTiles;
		// %PUBLIC%\Music\Sample Music
		REFKNOWNFOLDERID SampleMusic = FOLDERID_SampleMusic;
		// http://msdn.microsoft.com/zh-cn/library/windows/desktop/dd378457(v=vs.85).aspx 
	};
}