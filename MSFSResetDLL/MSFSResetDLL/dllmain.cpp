// dllmain.cpp : DLL 애플리케이션의 진입점을 정의합니다.
#include <Windows.h>
#include <SimConnect.h>

static HANDLE hSimConnect = NULL;

extern "C" __declspec(dllexport) void ResetAircraftPosition(double lat, double lon, double alt)
{
    if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Reset Aircraft DLL", NULL, 0, 0, 0))) {

        struct PositionData {
            double latitude;
            double longitude;
            double altitude;
        };

        PositionData pos = { lat, lon, alt };

        DWORD definitionId = 0;
        SimConnect_AddToDataDefinition(hSimConnect, definitionId, "PLANE LATITUDE", "degrees");
        SimConnect_AddToDataDefinition(hSimConnect, definitionId, "PLANE LONGITUDE", "degrees");
        SimConnect_AddToDataDefinition(hSimConnect, definitionId, "PLANE ALTITUDE", "feet");

        SimConnect_SetDataOnSimObject(hSimConnect, definitionId, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(pos), &pos);

        SimConnect_Close(hSimConnect);
    }
}