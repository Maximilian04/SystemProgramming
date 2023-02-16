#include <string.h>
#include <windows.h>
#include <stdio.h>

#include "voice.h"

namespace voice {
    static const size_t BUFFERSIZE = 2048;
    static char buffer[BUFFERSIZE] = {};
    static size_t currentPos = 0;

    static const char* codeTemplateBegin = ""
        "import os\n"
        "import torch\n"
        "\n"
        "device = torch.device('cpu')\n"
        "torch.set_num_threads(32)\n"
        "local_file = 'model.pt'\n"
        "\n"
        "if not os.path.isfile(local_file):\n"
        "    torch.hub.download_url_to_file('https://models.silero.ai/models/tts/en/v3_en.pt',\n"
        "                                   local_file)  \n"
        "\n"
        "model = torch.package.PackageImporter(local_file).load_pickle(\"tts_models\", \"model\")\n"
        "model.to(device)\n"
        "\n"
        // "#example_text = 'В недрах тундры выдры в г+етрах т+ырят в вёдра +ядра к+едров. А теперь сильно более длинный текст. Вообще не знаю, что и говорить тут. А ты знаешь? Я - нет!'\n"
        "example_text = '";
    static const char* codeTemplateEnd = ""
        "'\n"
        "#example_text = 'Is it suitable for you? I am glad you do.'\n"
        "sample_rate = 48000\n"
        "# speaker='baya'\n"
        "# speaker='xenia'\n"
        "speaker='en_5'\n"
        "\n"
        "audio_paths = model.save_wav(text=example_text,\n"
        "                             speaker=speaker,\n"
        "                             sample_rate=sample_rate)\n";

    /**
     * @brief Clear buffer
     *
     */
    void clear() {
        memset(buffer, 0, BUFFERSIZE * sizeof(char));
        currentPos = 0;
    }

    /**
     * @brief Add plain text to the end of buffer
     *
     * @param [in] str Text to add
     */
    void addText(char const* str) {
        size_t index = 0;
        while (str[index] != '\0') {
            buffer[currentPos + index] = str[index];
            index++;
        }
        currentPos += index;
    }

    /**
     * @brief Generate speach
     *
     */
    void generate() {
        char const* fileName = "stuff/speach.py";
        FILE* file = fopen(fileName, "wt, ccs=UTF-8");

        fprintf(file, codeTemplateBegin);
        fprintf(file, buffer);
        fprintf(file, codeTemplateEnd);

        fclose(file);

        system("python stuff/speach.py");
        PlaySound(TEXT("test.wav"), NULL, SND_FILENAME | SND_ASYNC);
    }
}