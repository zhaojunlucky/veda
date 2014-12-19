#pragma once
#include <Shlobj.h>
#pragma comment(lib,"Shell32.lib")
namespace veda
{
	enum SpecialFolder
	{
		/* 
		 * FOLDERID_AdminTools
		 * Version 5.0.The file system directory that is used to store administrative tools for an individual user.The MMC will save customized consoles to this directory, and it will roam with the user.
		 */
		AdminTools = CSIDL_ADMINTOOLS,
		/* 
		 * FOLDERID_Startup
		 * The file system directory that corresponds to the user's nonlocalized Startup program group. This value is recognized in Windows Vista for backward compatibility, but the folder itself no longer exists.
		 */
		Startup = CSIDL_ALTSTARTUP,
		/* 
		 * FOLDERID_RoamingAppData
		 * Version 4.71.The file system directory that serves as a common repository for application - specific data.A typical path is C : \Documents and Settings\username\Application Data.
		 */
		RoamingAppData = CSIDL_APPDATA,
		/*
		 * FOLDERID_RecycleBinFolder
		 * The virtual folder that contains the objects in the user's Recycle Bin.
		 */
		RecycleBinFolder = CSIDL_BITBUCKET,
		/*
		 * FOLDERID_CDBurning
		 * Version 6.0.The file system directory that acts as a staging area for files waiting to be written to a CD.A typical path is C : \Documents and Settings\username\Local Settings\Application Data\Microsoft\CD Burning.
		 */
		CDBurning = CSIDL_CDBURN_AREA,
		/*
		 * FOLDERID_CommonAdminTools
		 * Version 5.0.The file system directory that contains administrative tools for all users of the computer.
		 */
		CommonAdminTools = CSIDL_COMMON_ADMINTOOLS,
		/* 
		 * FOLDERID_ProgramData
		 * Version 5.0.The file system directory that contains application data for all users.A typical path is C : \Documents and Settings\All Users\Application Data.This folder is used for application data that is not user specific.For example, an application can store a spell - check dictionary, a database of clip art, or a log file in the CSIDL_COMMON_APPDATA folder.This information will not roam and is available to anyone using the computer.
		 */
		ProgramData = CSIDL_COMMON_APPDATA,
		/*
		 * FOLDERID_PublicDesktop
		 * The file system directory that contains files and folders that appear on the desktop for all users.A typical path is C : \Documents and Settings\All Users\Desktop.
		 */
		PublicDesktop = CSIDL_COMMON_DESKTOPDIRECTORY,
		/*
		 * FOLDERID_PublicDocuments
		 * The file system directory that contains documents that are common to all users.A typical path is C : \Documents and Settings\All Users\Documents.
		*/
		PublicDocuments = CSIDL_COMMON_DOCUMENTS,
		/*
		 * FOLDERID_Favorites
		 * The file system directory that serves as a common repository for favorite items common to all users.
		*/
		CommonFavorites = CSIDL_COMMON_FAVORITES,
		/*
		 * FOLDERID_PublicMusic
		 * Version 6.0.The file system directory that serves as a repository for music files common to all users.A typical path is C : \Documents and Settings\All Users\Documents\My Music.
		 */
		PublicMusic = CSIDL_COMMON_MUSIC,
		/* 
		 * FOLDERID_CommonOEMLinks
		 * This value is recognized in Windows Vista for backward compatibility, but the folder itself is no longer used.
		 */
		CommonOEMLinks = CSIDL_COMMON_OEM_LINKS,
		/*
		 * FOLDERID_PublicPictures
		 * Version 6.0.The file system directory that serves as a repository for image files common to all users.A typical path is C : \Documents and Settings\All Users\Documents\My Pictures.
		 */
		PublicPictures = CSIDL_COMMON_PICTURES,
		/*
		 * FOLDERID_CommonPrograms
		 * The file system directory that contains the directories for the common program groups that appear on the Start menu for all users.A typical path is C : \Documents and Settings\All Users\Start Menu\Programs.
		 */
		CommonPrograms = CSIDL_COMMON_PROGRAMS,
		/*
		 * FOLDERID_CommonStartMenu
		 * The file system directory that contains the programs and folders that appear on the Start menu for all users.A typical path is C : \Documents and Settings\All Users\Start Menu.
		 */
		CommonStartMenu = CSIDL_COMMON_STARTMENU,
		/*
		 * FOLDERID_CommonStartup
		 * The file system directory that contains the programs that appear in the Startup folder for all users.A typical path is C:\Documents and Settings\All Users\Start Menu\Programs\Startup.
		 */
		CommonStartup = CSIDL_COMMON_STARTUP,
		/*
		 * FOLDERID_CommonTemplates
		 * The file system directory that contains the templates that are available to all users.A typical path is C : \Documents and Settings\All Users\Templates.
		 */
		CommonTemplates = CSIDL_COMMON_TEMPLATES,
		/*
		 * FOLDERID_PublicVideos
		 * Version 6.0.The file system directory that serves as a repository for video files common to all users.A typical path is C:\Documents and Settings\All Users\Documents\My Videos.
		 */
		PublicVideos = CSIDL_COMMON_VIDEO,
		/* 
		 * FOLDERID_NetworkFolder
		 * The folder that represents other computers in your workgroup.
		 */
		NetworkFolder = CSIDL_COMPUTERSNEARME,
		/*
		 * FOLDERID_ConnectionsFolder
		 * The virtual folder that represents Network Connections, that contains network and dial - up connections.
		 */
		ConnectionsFolder = CSIDL_CONNECTIONS,
		/*
		 * FOLDERID_ControlPanelFolder
		 * The virtual folder that contains icons for the Control Panel applications.
		 */
		ControlPanelFolder = CSIDL_CONTROLS,
		/*
		 * FOLDERID_Cookies
		 * The file system directory that serves as a common repository for Internet cookies.A typical path is C : \Documents and Settings\username\Cookies.
		 */
		Cookies = CSIDL_COOKIES,
		/*
		 * FOLDERID_Desktop
		 * The virtual folder that represents the Windows desktop, the root of the namespace.
		 */
		VirtualDesktop = CSIDL_DESKTOP,
		/*
		 * FOLDERID_Desktop
		 * The file system directory used to physically store file objects on the desktop(not to be confused with the desktop folder itself).A typical path is C : \Documents and Settings\username\Desktop.
		 */
		Desktop = CSIDL_DESKTOPDIRECTORY,
		/*
		 * FOLDERID_ComputerFolder
		 * The virtual folder that represents My Computer, containing everything on the local computer : storage devices, printers, and Control Panel.The folder can also contain mapped network drives.
		 */
		ComputerFolder = CSIDL_DRIVES,
		/*
		 * FOLDERID_Favorites
		 * The file system directory that serves as a common repository for the user's favorite items. A typical path is C:\Documents and Settings\username\Favorites.
		 */
		Favorites = CSIDL_FAVORITES,
		/*
		 * FOLDERID_Fonts
		 * A virtual folder that contains fonts.A typical path is C:\Windows\Fonts.
		 */
		Fonts = CSIDL_FONTS,
		/*
		 * FOLDERID_History
		 * The file system directory that serves as a common repository for Internet history items.
		 */
		History = CSIDL_HISTORY,
		/*
		 * FOLDERID_InternetFolder
		 * A virtual folder for Internet Explorer.
		 */
		InternetFolder = CSIDL_INTERNET,
		/* 
		 * FOLDERID_InternetCache
		 * Version 4.72.The file system directory that serves as a common repository for temporary Internet files.A typical path is C : \Documents and Settings\username\Local Settings\Temporary Internet Files.
		 */
		InternetCache = CSIDL_INTERNET_CACHE,
		/*
		 * FOLDERID_LocalAppData
		 * Version 5.0.The file system directory that serves as a data repository for local(nonroaming) applications.A typical path is C : \Documents and Settings\username\Local Settings\Application Data.
		 */
		LocalAppData = CSIDL_LOCAL_APPDATA,
		/*
		 * FOLDERID_Documents
		 * Version 6.0.The virtual folder that represents the My Documents desktop item.This value is equivalent to CSIDL_PERSONAL.
		 */
		Documents = CSIDL_MYDOCUMENTS,
		/*
		 * FOLDERID_Music
		 * The file system directory that serves as a common repository for music files.A typical path is C : \Documents and Settings\User\My Documents\My Music.
		 */
		Music = CSIDL_MYMUSIC,
		/*
		 * FOLDERID_Pictures
		 * Version 5.0.The file system directory that serves as a common repository for image files.A typical path is C : \Documents and Settings\username\My Documents\My Pictures.
		 */
		Pictures = CSIDL_MYPICTURES,
		/*
		 * FOLDERID_Videos
		 * Version 6.0.The file system directory that serves as a common repository for video files.A typical path is C : \Documents and Settings\username\My Documents\My Videos.
		 */
		Videos = CSIDL_MYVIDEO,
		/*
		 * FOLDERID_NetHood
		 * A file system directory that contains the link objects that may exist in the My Network Places virtual folder.It is not the same as CSIDL_NETWORK, which represents the network namespace root.A typical path is C : \Documents and Settings\username\NetHood.
		 */
		NetHood = CSIDL_NETHOOD,
		/* 
		 * FOLDERID_NetworkFolder
		 * A virtual folder that represents Network Neighborhood, the root of the network namespace hierarchy.
		 */
		VirtualNetworkFolder = CSIDL_NETWORK,
		/*
		 * FOLDERID_Documents
		 * Version 6.0.The virtual folder that represents the My Documents desktop item.This is equivalent to CSIDL_MYDOCUMENTS.
		 * Previous to Version 6.0.The file system directory used to physically store a user's common repository of documents. A typical path is C:\Documents and Settings\username\My Documents. This should be distinguished from the virtual My Documents folder in the namespace. To access that virtual folder, use SHGetFolderLocation, which returns the ITEMIDLIST for the virtual location, or refer to the technique described in Managing the File System.
		 */
		MyDocuments = CSIDL_PERSONAL,
		/*
		 * FOLDERID_PrintersFolder
		 * The virtual folder that contains installed printers.
		*/
		PrintersFolder = CSIDL_PRINTERS,
		/*
		 * FOLDERID_PrintHood
		 * The file system directory that contains the link objects that can exist in the Printers virtual folder.A typical path is C : \Documents and Settings\username\PrintHood.
		 */
		PrintHood = CSIDL_PRINTHOOD,
		/* 
		 * FOLDERID_Profile
		 * Version 5.0.The user's profile folder. A typical path is C:\Users\username. Applications should not create files or folders at this level; they should put their data under the locations referred to by CSIDL_APPDATA or CSIDL_LOCAL_APPDATA. However, if you are creating a new Known Folder the profile root referred to by CSIDL_PROFILE is appropriate.
		 */
		Profile = CSIDL_PROFILE,
		/*
		 * FOLDERID_ProgramFiles
		 * Version 5.0.The Program Files folder.A typical path is C : \Program Files.
		 */
		ProgramFiles = CSIDL_PROGRAM_FILES,
		/*
		 * FOLDERID_ProgramFilesX86
		 */
		ProgramFilesX86 = CSIDL_PROGRAM_FILESX86,
		/*
		 * FOLDERID_ProgramFilesCommon
		 * Version 5.0.A folder for components that are shared across applications.A typical path is C : \Program Files\Common.Valid only for Windows XP.
		 */
		ProgramFilesCommon = CSIDL_PROGRAM_FILES_COMMON,
		/*
		 * FOLDERID_ProgramFilesCommonX86
		 */
		ProgramFilesCommonX86 = CSIDL_PROGRAM_FILES_COMMONX86,
		/*
		 * FOLDERID_Programs
		 * The file system directory that contains the user's program groups (which are themselves file system directories). A typical path is C:\Documents and Settings\username\Start Menu\Programs.
		 */
		Programs = CSIDL_PROGRAMS,
		/*
		 * FOLDERID_Recent
		 * The file system directory that contains shortcuts to the user's most recently used documents. A typical path is C:\Documents and Settings\username\My Recent Documents. To create a shortcut in this folder, use SHAddToRecentDocs. In addition to creating the shortcut, this function updates the Shell's list of recent documents and adds the shortcut to the My Recent Documents submenu of the Start menu.
		 */
		Recent = CSIDL_RECENT,
		/*
		 * FOLDERID_ResourceDir
		 * Windows Vista.The file system directory that contains resource data.A typical path is C : \Windows\Resources.
		 */
		ResourceDir = CSIDL_RESOURCES,
		/*
		 * FOLDERID_LocalizedResourcesDir
		 */
		LocalizedResourcesDir = CSIDL_RESOURCES_LOCALIZED,
		/*
		 * FOLDERID_SendTo
		 * The file system directory that contains Send To menu items.A typical path is C : \Documents and Settings\username\SendTo.
		 */
		SendTo = CSIDL_SENDTO,
		/*
		 * FOLDERID_StartMenu
		 * The file system directory that contains Start menu items.A typical path is C : \Documents and Settings\username\Start Menu.
		 */
		StartMenu = CSIDL_STARTMENU,
		/*
         * FOLDERID_Startup
		 * The file system directory that corresponds to the user's Startup program group. The system starts these programs whenever the associated user logs on. A typical path is C:\Documents and Settings\username\Start Menu\Programs\Startup.
		 */
		UserStartup = CSIDL_STARTUP,
		/* 
		 * FOLDERID_System
		 * Version 5.0.The Windows System folder.A typical path is C : \Windows\System32.
		 */
		System = CSIDL_SYSTEM,
		/*
		 * FOLDERID_SystemX86
		 */
		SystemX86 = CSIDL_SYSTEMX86,
		/*
		 * FOLDERID_Templates
		 * The file system directory that serves as a common repository for document templates.A typical path is C : \Documents and Settings\username\Templates.
		 */
		Templates = CSIDL_TEMPLATES,
		/*
		 * FOLDERID_Windows
		 * Version 5.0.The Windows directory or SYSROOT.This corresponds to the %windir% or %SYSTEMROOT% environment variables.A typical path is C : \Windows.
		 */
		Windows = CSIDL_WINDOWS
		/*Flags = Flags,
		CSIDL_FLAG_CREATE
		KF_FLAG_CREATE
		Version 5.0.Combine with another CSIDL to force the creation of the associated folder if it does not exist.
		CSIDL_FLAG_DONT_UNEXPAND
		KF_FLAG_DONT_UNEXPAND
		Combine with another CSIDL constant to ensure the expansion of environment variables.
		CSIDL_FLAG_DONT_VERIFY
		KF_FLAG_DONT_VERIFY
		Combine with another CSIDL constant, except for CSIDL_FLAG_CREATE, to return an unverified folder path with no attempt to create or initialize the folder.
		CSIDL_FLAG_NO_ALIAS
		KF_FLAG_NO_ALIAS
		Combine with another CSIDL constant to ensure the retrieval of the true system path for the folder, free of any aliased placeholders such as %USERPROFILE%, returned by SHGetFolderLocation.This flag has no effect on paths returned by SHGetFolderPath.
		CSIDL_FLAG_PER_USER_INIT
		CSIDL_FLAG_MASK*/
	};
}