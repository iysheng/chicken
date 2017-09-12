/*
 * multask.c
 *
 *  Created on: 2017��9��12��
 *      Author: iysheng
 */

#include "main.h"

/*
*********************************************************************************************************
*        �� �� ��: _cbCallbackT0
*        ����˵��: ����0�Ļص�����
*        ��    �Σ�pMsg  ��Ϣָ��
*        �� �� ֵ: ��
*********************************************************************************************************
*/
static void _cbCallbackT0(WM_MESSAGE * pMsg)
{
switch (pMsg->MsgId)
{
case WM_PAINT:
/* Handle the paint message */
GUI_SetBkColor(GUI_RED);
GUI_SetColor(GUI_BLACK);
GUI_SetFont(&GUI_FontComic24B_ASCII);
GUI_Clear();
GUI_DispStringAt("Task0 Moving", 0, 0);
break;
default:
WM_DefaultProc(pMsg);
}
}

/*
*********************************************************************************************************
*        �� �� ��: _cbBackgroundWin
*        ����˵��: �������ڵĻص�����
*        ��    �Σ�pMsg  ��Ϣָ��
*        �� �� ֵ: ��
*********************************************************************************************************
*/
static void _cbBackgroundWin(WM_MESSAGE* pMsg)
{
switch (pMsg->MsgId)
{
case WM_PAINT:
/* Handle only the paint message */
GUI_SetBkColor(0x00CC00);
GUI_Clear();
GUI_SetFont(&GUI_Font24_ASCII);
GUI_DispStringHCenterAt("STemWin - multitasking demo\n", 159, 5);
GUI_SetFont(&GUI_Font13_1);
GUI_DispStringAt("Scrolling text and moving windows without flickering", 5, 35);
default:
WM_DefaultProc(pMsg);
}
}

/*
*********************************************************************************************************
*        �� �� ��: Task_0
*        ����˵��: GUI����0
*        ��    �Σ���
*        �� �� ֵ: ��
*********************************************************************************************************
*/
void Task_0(void)
{
/* Create frame window */
FRAMEWIN_Handle hFrameWin = FRAMEWIN_Create("Task 0",  NULL, WM_CF_SHOW | WM_CF_STAYONTOP,  0, 230, 200,
 40);
/* Create child window */
WM_HWIN      hChildWin = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetClientWindow(hFrameWin),
  WM_CF_SHOW | WM_CF_MEMDEV,  _cbCallbackT0, 0);
FRAMEWIN_SetActive(hFrameWin, 0);
/* Make sure the right window is active... */
WM_SelectWindow(hChildWin);
/* ...and the right font is selected */
GUI_SetFont(&GUI_FontComic24B_ASCII);
while(1)
{
int i;
int nx = 80;
/* Move window continously */
for (i = 0; i < nx; i++)
{
WM_MoveWindow(hFrameWin, 2, 0);
GUI_Delay(50);
}
for (i = 0; i < nx; i++)
{
WM_MoveWindow(hFrameWin, -2, 0);
GUI_Delay(50);
}
}
}

/*
*********************************************************************************************************
*        �� �� ��: MainTask
*        ����˵��: GUI����0
*        ��    �Σ���
*        �� �� ֵ: ��
*********************************************************************************************************
*/
void MainTask(void)
{
GUI_Init();
WM_SetCreateFlags(WM_CF_MEMDEV);
WM_SetCallback(WM_HBKWIN, _cbBackgroundWin);
while(1)
{
Task_0();
}
}

/*
*********************************************************************************************************
*        �� �� ��: _cbCallbackT1
*        ����˵��: ����1�Ļص�����
*        ��    �Σ�pMsg  ��Ϣָ��
*        �� �� ֵ: ��
*********************************************************************************************************
*/
static void _cbCallbackT1(WM_MESSAGE * pMsg)
{
WM_HWIN hWin = (FRAMEWIN_Handle)(pMsg->hWin);
switch (pMsg->MsgId)
{
case WM_PAINT:
/* Handle the paint message */
GUI_SetBkColor(GUI_BLUE);
GUI_SetColor(GUI_WHITE);
GUI_SetFont(&GUI_FontComic24B_ASCII);
GUI_SetTextAlign(GUI_TA_HCENTER | GUI_TA_VCENTER);
GUI_Clear();
GUI_DispStringHCenterAt("Task1 window...",
WM_GetWindowSizeX(hWin) / 2,
WM_GetWindowSizeY(hWin) / 2);
break;
default:
WM_DefaultProc(pMsg);
}
}

/*
*********************************************************************************************************
*        �� �� ��: Task_1
*        ����˵��: GUI����0
*        ��    �Σ���
*        �� �� ֵ: ��
*********************************************************************************************************
*/
void Task_1(void)
{
/* Create frame window */
FRAMEWIN_Handle hFrameWin = FRAMEWIN_Create("Task 1", NULL, WM_CF_SHOW | WM_CF_STAYONTOP,
20, 170, 200, 40);
/* Create child window */
WM_HWIN hChildWin = WM_CreateWindowAsChild(0, 0, 0, 0, WM_GetClientWindow(hFrameWin), WM_CF_SHOW |
WM_CF_MEMDEV,_cbCallbackT1, 0);
FRAMEWIN_SetActive(hFrameWin, 0);
while(1)
{
int i;
int nx = 80;
int ny = 90;
/* Move window continously */
for (i = 0; i < ny; i++)
{
WM_MoveWindow(hFrameWin, 0, -2);
GUI_Delay(50);
}
for (i = 0; i < nx; i++)
{
WM_MoveWindow(hFrameWin, 2, 0);
GUI_Delay(50);
}
for (i = 0; i < ny; i++)
{
WM_MoveWindow(hFrameWin, 0, 2);
GUI_Delay(50);
}
for (i = 0; i < nx; i++)
{
WM_MoveWindow(hFrameWin, -2, 0);
GUI_Delay(50);
}
}
}

