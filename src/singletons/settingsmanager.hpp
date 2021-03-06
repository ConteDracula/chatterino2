#pragma once

#include "messages/highlightphrase.hpp"
#include "messages/messageelement.hpp"
#include "singletons/helper/chatterinosetting.hpp"

#include <pajlada/settings/setting.hpp>
#include <pajlada/settings/settinglistener.hpp>

namespace chatterino {
namespace singletons {

static void _registerSetting(std::weak_ptr<pajlada::Settings::ISettingData> setting);

class SettingManager : public QObject
{
    Q_OBJECT

    using BoolSetting = ChatterinoSetting<bool>;
    using FloatSetting = ChatterinoSetting<float>;
    using IntSetting = ChatterinoSetting<int>;
    using StringSetting = ChatterinoSetting<std::string>;
    using QStringSetting = ChatterinoSetting<QString>;

public:
    messages::MessageElement::Flags getWordTypeMask();
    bool isIgnoredEmote(const QString &emote);

    void init();

    /// Appearance
    BoolSetting showTimestamps = {"/appearance/messages/showTimestamps", true};
    QStringSetting timestampFormat = {"/appearance/messages/timestampFormat", "h:mm"};
    BoolSetting showBadges = {"/appearance/messages/showBadges", true};
    BoolSetting showLastMessageIndicator = {"/appearance/messages/showLastMessageIndicator", false};
    BoolSetting hideEmptyInput = {"/appearance/hideEmptyInputBox", false};
    BoolSetting showMessageLength = {"/appearance/messages/showMessageLength", false};
    BoolSetting seperateMessages = {"/appearance/messages/separateMessages", false};
    BoolSetting windowTopMost = {"/appearance/windowAlwaysOnTop", false};
    BoolSetting hideTabX = {"/appearance/hideTabX", false};
    BoolSetting hidePreferencesButton = {"/appearance/hidePreferencesButton", false};
    BoolSetting hideUserButton = {"/appearance/hideUserButton", false};
    BoolSetting enableSmoothScrolling = {"/appearance/smoothScrolling", true};
    BoolSetting enableSmoothScrollingNewMessages = {"/appearance/smoothScrollingNewMessages",
                                                    false};
    // BoolSetting useCustomWindowFrame = {"/appearance/useCustomWindowFrame", false};

    /// Behaviour
    BoolSetting allowDuplicateMessages = {"/behaviour/allowDuplicateMessages", true};
    BoolSetting mentionUsersWithAt = {"/behaviour/mentionUsersWithAt", false};
    FloatSetting mouseScrollMultiplier = {"/behaviour/mouseScrollMultiplier", 1.0};
    QStringSetting streamlinkPath = {"/behaviour/streamlink/path", ""};
    QStringSetting preferredQuality = {"/behaviour/streamlink/quality", "Choose"};
    BoolSetting pauseChatHover = {"/behaviour/pauseChatHover", false};

    /// Commands
    BoolSetting allowCommandsAtEnd = {"/commands/allowCommandsAtEnd", false};

    /// Emotes
    BoolSetting scaleEmotesByLineHeight = {"/emotes/scaleEmotesByLineHeight", false};
    BoolSetting enableTwitchEmotes = {"/emotes/enableTwitchEmotes", true};
    BoolSetting enableBttvEmotes = {"/emotes/enableBTTVEmotes", true};
    BoolSetting enableFfzEmotes = {"/emotes/enableFFZEmotes", true};
    BoolSetting enableEmojis = {"/emotes/enableEmojis", true};
    BoolSetting enableGifAnimations = {"/emotes/enableGifAnimations", true};
    FloatSetting emoteScale = {"/emotes/scale", 1.f};

    // 0 = Smallest size
    // 1 = One size above 0 (usually size of 0 * 2)
    // 2 = One size above 1 (usually size of 1 * 2)
    // etc...
    IntSetting preferredEmoteQuality = {"/emotes/preferredEmoteQuality", 0};

    /// Links
    BoolSetting linksDoubleClickOnly = {"/links/doubleClickToOpen", false};

    /// Moderation
    QStringSetting moderationActions = {"/moderation/actions", "/ban {user}\n/timeout {user} 300"};

    /// Highlighting
    BoolSetting enableHighlights = {"/highlighting/enabled", true};
    BoolSetting enableHighlightsSelf = {"/highlighting/nameIsHighlightKeyword", true};
    BoolSetting enableHighlightSound = {"/highlighting/enableSound", true};
    BoolSetting enableHighlightTaskbar = {"/highlighting/enableTaskbarFlashing", true};
    BoolSetting customHighlightSound = {"/highlighting/useCustomSound", false};

    ChatterinoSetting<std::vector<messages::HighlightPhrase>> highlightProperties = {
        "/highlighting/highlights"};

    QStringSetting pathHighlightSound = {"/highlighting/highlightSoundPath",
                                         "qrc:/sounds/ping2.wav"};
    QStringSetting highlightUserBlacklist = {"/highlighting/blacklistedUsers", ""};

    BoolSetting highlightAlwaysPlaySound = {"/highlighting/alwaysPlaySound", false};

    BoolSetting inlineWhispers = {"/whispers/enableInlineWhispers", true};

    static SettingManager &getInstance()
    {
        static SettingManager instance;
        return instance;
    }
    void updateWordTypeMask();

    void saveSnapshot();
    void recallSnapshot();

signals:
    void wordTypeMaskChanged();

private:
    std::unique_ptr<rapidjson::Document> snapshot;

    SettingManager();

    messages::MessageElement::Flags wordTypeMask = messages::MessageElement::Default;

    pajlada::Settings::SettingListener wordMaskListener;
};

}  // namespace singletons
}  // namespace chatterino
