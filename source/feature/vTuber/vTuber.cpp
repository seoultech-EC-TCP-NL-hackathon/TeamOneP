//
// Created by dlwog on 25. 10. 26..
//

#ifndef MYPROJECT_VTUBER_HPP
#define MYPROJECT_VTUBER_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

struct Vec3 { double x{}, y{}, z{}; };
struct Quat { double x{}, y{}, z{}, w{}; };

struct FileReferences {
    std::string Icon, Model, IdleAnimation, IdleAnimationWhenTrackingLost;
};

struct ModelSaveMetadata {
    std::string LastSavedVTubeStudioVersion;
    std::string LastSavedPlatform;
    std::string LastSavedDateUTC;
    std::string LastSavedDateLocalTime;
    std::string LastSavedDateUnixMillisecondTimestamp;
};

struct SavedModelPosition {
    Vec3 Position;
    Quat Rotation;
    Vec3 Scale;
};

struct ModelPositionMovement {
    bool Use{};
    double X{}, Y{}, Z{};
    double SmoothingX{}, SmoothingY{}, SmoothingZ{};
};

struct ItemSettings {
    bool OnlyMoveWhenPinned{};
    bool AllowNormalHotkeyTriggers{};
    double Multiplier_HeadAngleX{}, Multiplier_HeadAngleY{}, Multiplier_HeadAngleZ{};
    double Shift_HeadAngleX{}, Shift_HeadAngleY{};
    double Smoothing_HeadAngleX{}, Smoothing_HeadAngleY{}, Smoothing_HeadAngleZ{};
};

struct PhysicsSettings {
    bool Use{};
    bool UseLegacyPhysics{};
    int Live2DPhysicsFPS{};
    double PhysicsStrength{}, WindStrength{}, DraggingPhysicsStrength{};
};

struct GeneralSettings {
    double TimeUntilTrackingLostIdleAnimation{};
    bool WorkshopSharingForbidden{};
    bool EnableExpressionSaving{};
};

struct ParameterSetting {
    std::string Folder;
    std::string Name;
    std::string Input;
    double InputRangeLower{}, InputRangeUpper{};
    double OutputRangeLower{}, OutputRangeUpper{};
    bool ClampInput{}, ClampOutput{}, UseBlinking{}, UseBreathing{};
    std::string OutputLive2D;
    double Smoothing{};
    bool Minimized{};
};

struct Root {
    int Version{};
    std::string Name;
    std::string ModelID;

    FileReferences FileReferencesData;
    ModelSaveMetadata ModelSaveMetadataData;
    SavedModelPosition SavedModelPositionData;
    ModelPositionMovement ModelPositionMovementData;
    ItemSettings ItemSettingsData;
    PhysicsSettings PhysicsSettingsData;
    GeneralSettings GeneralSettingsData;

    std::vector<ParameterSetting> ParameterSettings;
};

/// === JSON 변환 === ///
void from_json(const json& j, Vec3& v) {
    j.at("x").get_to(v.x);
    j.at("y").get_to(v.y);
    j.at("z").get_to(v.z);
}
void from_json(const json& j, Quat& q) {
    j.at("x").get_to(q.x);
    j.at("y").get_to(q.y);
    j.at("z").get_to(q.z);
    j.at("w").get_to(q.w);
}
void from_json(const json& j, FileReferences& f) {
    j.at("Icon").get_to(f.Icon);
    j.at("Model").get_to(f.Model);
    j.at("IdleAnimation").get_to(f.IdleAnimation);
    j.at("IdleAnimationWhenTrackingLost").get_to(f.IdleAnimationWhenTrackingLost);
}
void from_json(const json& j, ModelSaveMetadata& m) {
    j.at("LastSavedVTubeStudioVersion").get_to(m.LastSavedVTubeStudioVersion);
    j.at("LastSavedPlatform").get_to(m.LastSavedPlatform);
    j.at("LastSavedDateUTC").get_to(m.LastSavedDateUTC);
    j.at("LastSavedDateLocalTime").get_to(m.LastSavedDateLocalTime);
    j.at("LastSavedDateUnixMillisecondTimestamp").get_to(m.LastSavedDateUnixMillisecondTimestamp);
}
void from_json(const json& j, SavedModelPosition& s) {
    j.at("Position").get_to(s.Position);
    j.at("Rotation").get_to(s.Rotation);
    j.at("Scale").get_to(s.Scale);
}
void from_json(const json& j, ModelPositionMovement& m) {
    j.at("Use").get_to(m.Use);
    j.at("X").get_to(m.X);
    j.at("Y").get_to(m.Y);
    j.at("Z").get_to(m.Z);
    j.at("SmoothingX").get_to(m.SmoothingX);
    j.at("SmoothingY").get_to(m.SmoothingY);
    j.at("SmoothingZ").get_to(m.SmoothingZ);
}
void from_json(const json& j, ItemSettings& i) {
    j.at("OnlyMoveWhenPinned").get_to(i.OnlyMoveWhenPinned);
    j.at("AllowNormalHotkeyTriggers").get_to(i.AllowNormalHotkeyTriggers);
    j.at("Multiplier_HeadAngleX").get_to(i.Multiplier_HeadAngleX);
    j.at("Multiplier_HeadAngleY").get_to(i.Multiplier_HeadAngleY);
    j.at("Multiplier_HeadAngleZ").get_to(i.Multiplier_HeadAngleZ);
    j.at("Shift_HeadAngleX").get_to(i.Shift_HeadAngleX);
    j.at("Shift_HeadAngleY").get_to(i.Shift_HeadAngleY);
    j.at("Smoothing_HeadAngleX").get_to(i.Smoothing_HeadAngleX);
    j.at("Smoothing_HeadAngleY").get_to(i.Smoothing_HeadAngleY);
    j.at("Smoothing_HeadAngleZ").get_to(i.Smoothing_HeadAngleZ);
}
void from_json(const json& j, PhysicsSettings& p) {
    j.at("Use").get_to(p.Use);
    j.at("UseLegacyPhysics").get_to(p.UseLegacyPhysics);
    j.at("Live2DPhysicsFPS").get_to(p.Live2DPhysicsFPS);
    j.at("PhysicsStrength").get_to(p.PhysicsStrength);
    j.at("WindStrength").get_to(p.WindStrength);
    j.at("DraggingPhysicsStrength").get_to(p.DraggingPhysicsStrength);
}
void from_json(const json& j, GeneralSettings& g) {
    j.at("TimeUntilTrackingLostIdleAnimation").get_to(g.TimeUntilTrackingLostIdleAnimation);
    j.at("WorkshopSharingForbidden").get_to(g.WorkshopSharingForbidden);
    j.at("EnableExpressionSaving").get_to(g.EnableExpressionSaving);
}
void from_json(const json& j, ParameterSetting& p) {
    j.at("Folder").get_to(p.Folder);
    j.at("Name").get_to(p.Name);
    j.at("Input").get_to(p.Input);
    j.at("InputRangeLower").get_to(p.InputRangeLower);
    j.at("InputRangeUpper").get_to(p.InputRangeUpper);
    j.at("OutputRangeLower").get_to(p.OutputRangeLower);
    j.at("OutputRangeUpper").get_to(p.OutputRangeUpper);
    j.at("ClampInput").get_to(p.ClampInput);
    j.at("ClampOutput").get_to(p.ClampOutput);
    j.at("UseBlinking").get_to(p.UseBlinking);
    j.at("UseBreathing").get_to(p.UseBreathing);
    j.at("OutputLive2D").get_to(p.OutputLive2D);
    j.at("Smoothing").get_to(p.Smoothing);
    j.at("Minimized").get_to(p.Minimized);
}
void from_json(const json& j, Root& r) {
    j.at("Version").get_to(r.Version);
    j.at("Name").get_to(r.Name);
    j.at("ModelID").get_to(r.ModelID);
    j.at("FileReferences").get_to(r.FileReferencesData);
    j.at("ModelSaveMetadata").get_to(r.ModelSaveMetadataData);
    j.at("SavedModelPosition").get_to(r.SavedModelPositionData);
    j.at("ModelPositionMovement").get_to(r.ModelPositionMovementData);
    j.at("ItemSettings").get_to(r.ItemSettingsData);
    j.at("PhysicsSettings").get_to(r.PhysicsSettingsData);
    j.at("GeneralSettings").get_to(r.GeneralSettingsData);
    j.at("ParameterSettings").get_to(r.ParameterSettings);
}

int main() {
    std::ifstream f("C:/Users/dlwog/OneDrive/Desktop/VkMain-out/assets/vTuber/TUBASA_014/TUBASA_014.vtube.json");
    if (!f) {
        std::cerr << "파일을 열 수 없습니다.\n";
        return 1;
    }

    json j;
    f >> j;
    Root model = j.get<Root>();

    std::cout << "Model Name: " << model.Name << "\n";
    std::cout << "Model File: " << model.FileReferencesData.Model << "\n";
    std::cout << "Param count: " << model.ParameterSettings.size() << "\n";
    std::cout << "First Param Name: " << model.ParameterSettings.front().Name << "\n";
}

#endif //MYPROJECT_VTUBER_HPP