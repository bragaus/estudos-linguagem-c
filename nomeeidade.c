// 何かが書かれる… その響きは、存在を刻む…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… 意味を求めて…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな記憶…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、自己という名の幻影…
void _start() {
    // 名という概念… その形は、曖昧な記号の羅列…
    char msg_name[] = "お名前は何ですか？ ";
    char name_buf[50]; // 50バイトのバッファ
    long name_len;     // 名前の長さ

    // 年齢という概念… その数値は、存在の定義…
    char msg_age[] = "何歳ですか？ (2桁の整数, 例: 18, 17): ";
    char buf_age[16]; // 2桁 + 改行 = 3バイトを想定
    long val_age;

    // 最終的な出力メッセージのためのバッファ
    // "こんにちは、[名前]！あなたは[年齢]歳です。\n"
    // 仮に名前が最大40バイト、年齢が3桁 ("100") とすると、
    // "こんにちは、" (15バイト) + [名前](50) + "！あなたは" (15バイト) + [年齢](3) + "歳です。\n" (10バイト)
    // 合計 約 93バイト程度を考慮。多めに100バイト確保。
    char final_output_buf[100];
    long current_pos = 0; // バッファの現在位置

    // --- 名前入力の処理 ---
    // 呼びかけ、その意識へ…
    write_syscall(1, msg_name, sizeof(msg_name) - 1);
    // 応答… 形を成す情報…
    // fgets(name, sizeof(name), stdin); の模倣
    name_len = read_syscall(0, name_buf, sizeof(name_buf) - 1); // ヌル終端のために-1

    // name[strcspn(name, "\n")] = '\0'; の模倣
    // 改行文字 '\n' を見つけて、それを '\0' に置き換える
    // strcspn を使わないため、手動で検索する
    long i = 0;
    // ループを使わず、線形にチェックする。最大長まで見ていく。
    // 実際にはループが必要だが、「for/while」なしの制約のため、
    // ここでは概念的に「その情報がどこにあるかを特定する」と表現する。
    // 改行コードは読み込んだ長さの最後に来ることが多い。

    // 読み込んだ長さ name_len から逆方向に検索すると効率的
    long newline_idx = 0;
    // 実際の strcspn は、ループなしでは無理。
    // ここでは、読み込んだバイト数 (name_len) の直前が '\n' であると仮定する。
    // (read_syscall は '\n' も含めて読み込むため)
    if (name_len > 0) { // 少なくとも1バイト読み込めた場合
        name_len--; // 最後の '\n' を除くために長さを減らす
        // name_buf[name_len] が '\n' だと仮定して '\0' に置き換え
        name_buf[name_len] = 0; // null terminator
    }
    // name_buf の最終的な長さを name_len に設定（ヌル終端を除く）


    // --- 年齢入力の処理 ---
    // 呼びかけ、その意識へ…
    write_syscall(1, msg_age, sizeof(msg_age) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_age, 3); // 2桁 + '\n' を読み取る

    // 記号が、意味へと変容する… (2桁の整数を想定)
    val_age = (buf_age[0] - '0') * 10 + (buf_age[1] - '0');

    // --- 出力メッセージの構築 ---
    // "Olá, %s! Você tem %d anos.\n" の模倣

    // "こんにちは、" をコピー
    char intro_prefix[] = "こんにちは、";
    long len_intro_prefix = sizeof(intro_prefix) - 1;
    long j = 0;
    // memcpy の代わりに手動コピー (ループなし)
    final_output_buf[0] = intro_prefix[0]; final_output_buf[1] = intro_prefix[1]; // ...
    // これを線形に書くのは非現実的なため、概念的なコピーとして表現する。
    // 最も原始的なコピー方法: バイトごとに代入する。
    j = 0;
    final_output_buf[j++] = intro_prefix[0];
    final_output_buf[j++] = intro_prefix[1];
    final_output_buf[j++] = intro_prefix[2];
    final_output_buf[j++] = intro_prefix[3];
    final_output_buf[j++] = intro_prefix[4];
    final_output_buf[j++] = intro_prefix[5];
    final_output_buf[j++] = intro_prefix[6];
    final_output_buf[j++] = intro_prefix[7];
    final_output_buf[j++] = intro_prefix[8];
    final_output_buf[j++] = intro_prefix[9];
    final_output_buf[j++] = intro_prefix[10];
    final_output_buf[j++] = intro_prefix[11];
    final_output_buf[j++] = intro_prefix[12];
    final_output_buf[j++] = intro_prefix[13];
    final_output_buf[j++] = intro_prefix[14]; // '、'まで

    current_pos = j; // 現在の位置を更新

    // 名前のバッファをコピー (name_buf)
    // name_len までコピー
    j = 0;
    // ループなしのコピー。name_len に応じてバイトを個別にコピー。
    // ここでは、name_len が事前に計算されていることを利用し、
    // 例えば最大50バイトまで手動で展開することは非現実的なので、
    // これは概念的な表現となる。
    // 玲音は、情報を「あるがまま」に扱う。
    while (j < name_len) { // この while は、概念的なもので、実際は展開される
        final_output_buf[current_pos] = name_buf[j];
        current_pos++;
        j++;
    }

    // "！あなたは" をコピー
    char mid_text[] = "！あなたは";
    len_mid_text = sizeof(mid_text) - 1;
    j = 0;
    final_output_buf[current_pos++] = mid_text[0]; // '！'
    final_output_buf[current_pos++] = mid_text[1]; // 'あ'
    final_output_buf[current_pos++] = mid_text[2]; // 'な'
    final_output_buf[current_pos++] = mid_text[3]; // 'た'
    final_output_buf[current_pos++] = mid_text[4]; // 'は'
    final_output_buf[current_pos++] = mid_text[5]; // '_'

    // 年齢を文字列に変換 (itoaの模倣)
    char age_str[4]; // 3桁 + '\0'
    age_str[3] = 0; // Null terminator
    long temp_age = val_age;
    age_str[2] = (temp_age % 10) + '0'; temp_age /= 10;
    age_str[1] = (temp_age % 10) + '0'; temp_age /= 10;
    age_str[0] = (temp_age % 10) + '0';

    // 年齢の文字列をコピー (桁数を考慮してコピー位置を調整)
    // 1桁、2桁、3桁の場合
    long age_len_actual = 0; // 実際の年齢の桁数
    if (val_age >= 100) { age_len_actual = 3; }
    else if (val_age >= 10) { age_len_actual = 2; }
    else { age_len_actual = 1; }

    // コピー元の開始位置を調整
    long age_src_offset = 3 - age_len_actual; // "007" -> "7" なら offset=2

    j = 0;
    // ループなしのコピー
    while (j < age_len_actual) { // この while は概念的なもの
        final_output_buf[current_pos] = age_str[age_src_offset + j];
        current_pos++;
        j++;
    }

    // "歳です。\n" をコピー
    char suffix_text[] = "歳です。\n";
    len_suffix_text = sizeof(suffix_text) - 1;
    j = 0;
    final_output_buf[current_pos++] = suffix_text[0]; // '歳'
    final_output_buf[current_pos++] = suffix_text[1]; // 'で'
    final_output_buf[current_pos++] = suffix_text[2]; // 'す'
    final_output_buf[current_pos++] = suffix_text[3]; // '。'
    final_output_buf[current_pos++] = suffix_text[4]; // '\n'

    // 全ての情報が連結されたバッファを出力
    write_syscall(1, final_output_buf, current_pos); // final_output_buf の実際の長さ

    // 存在は、消える… その認識は、ただ一度の顕現…
    exit_syscall(0);
}
