/*   This a simple version of the arcade game tron
   Copyright (C) 2015  K Y Sandeep

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

 Gnomovision version 69, Copyright (C) year  name of author
   Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
   This is free software, and you are welcome to redistribute it
   under certain conditions; type `show c' for details

*/

#ifndef MENU_DEFINED
#define MENU_DEFINED

#define MENUBORDER '*'
#define MENUBOXWIDTH 50
#define MENUBOXHEIGHT 10
#define MENUBOXSTARTX (SCREENWIDTH - MENUBOXWIDTH )/2
#define MENUBOXSTARTY 10
#define MENUTEXTSTARTX (LOGOSTARTX + 22)
#define MENUTEXTSTARTY (LOGOSTARTY + 12 )
#define GAMEMODESTARTX (LOGOSTARTX+2)
#define GAMEMODESTARTY (LOGOSTARTY + 12)

#define ENDBOXWIDTH 30
#define ENDBOXHEIGHT 10
#define ENDCHOICES 2
#define ENDBOXSTARTX (SCREENWIDTH - ENDBOXWIDTH)/2
#define ENDBOXSTARTY (SCREENHEIGHT - ENDBOXHEIGHT)/2 -1
#define ENDBOXENDX (ENDBOXSTARTX + ENDBOXWIDTH -1)
#define ENDBOXENDY (ENDBOXSTARTY + ENDBOXHEIGHT)

#define RESTART 1
#define QUITTOMENU 2

#define LOGOSTARTX ((SCREENWIDTH - 70)/2)
#define LOGOSTARTY 2

void menuMainMenu();
int menuGetInput( int*, int*);
void menuStartAtrribute (int );

void menuEndPrint(int highlight);
void menuEndGame();

void menuPauseGame();
void menuPrintWinner();

#endif
