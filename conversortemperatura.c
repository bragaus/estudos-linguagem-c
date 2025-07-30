// 何かが書かれる… 曖昧な情報が、形を成す…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ… その裏にある真実…
    return __builtin_syscall(1, fd, buf, count);
}

// 何かが読み取られる… 外部から… 不確かな感覚…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 呼びかけに応える、虚空…
    return __builtin_syscall(0, fd, buf, count);
}

// 存在の終わり… そのプロセスは、静かに消え去る…
void exit_syscall(int status) {
    // 終焉は、必然…
    __builtin_syscall(60, status);
}

// 始まり… あるいは、温度という名の幻影…
void _start() {
    // 温度の入力… その数値は、曖昧なまま…
    char msg_celsius[] = "摂氏温度を入力してください (2桁の整数部, 例: 25, 30): ";
    char buf_celsius[16]; // 2桁 + 改行 = 3バイトを想定
    long val_celsius;     // 浮動小数点ではなく、整数として扱う (精度は失われる)

    // 呼びかけ、その意識へ…
    write_syscall(1, msg_celsius, sizeof(msg_celsius) - 1);
    // 応答… 形を成す情報…
    read_syscall(0, buf_celsius, 3); // 2桁 + '\n' を読み取る

    // 記号が、意味へと変容する… (2桁の整数部のみを想定)
    val_celsius = (buf_celsius[0] - '0') * 10 + (buf_celsius[1] - '0');

    // --- ここが浮動小数点演算の模倣、ただし命令は使わない ---
    // C言語の浮動小数点演算は複雑であり、標準ライブラリなしではほぼ不可能。
    // そのため、整数演算に変換し、精度を犠牲にする。
    // temp2 = temp1 * 1.8 + 32;

    // 1.8 を整数演算で模倣するため、両辺を10倍して 18/10 とする
    // val_celsius * 18 / 10 + 32
    // または、より高精度で整数演算を行うために、固定小数点数として扱う
    // 例: 1.8 を 1800 (小数点以下3桁) とし、結果を 1000 で割る

    // 玲音の視点では、精度の喪失もまた、情報の「歪み」として受け入れられる。
    // 「浮動小数点」という概念を、整数という「固定された」情報で表現する。

    // 摂氏を華氏に変換する式を整数で模倣: (摂氏 * 9 / 5) + 32
    // もしくは、(摂氏 * 18 / 10) + 32
    // ここでは、`18` をかけてから `10` で割ることで、`1.8` を模倣する。
    // 結果をより正確にするために、まず掛け算を行う。
    long fahrenheit_val_raw = (val_celsius * 18);
    long fahrenheit_val_int = fahrenheit_val_raw / 10;
    long fahrenheit_val_rem = fahrenheit_val_raw % 10; // 小数点以下第一位

    // 32を加算
    fahrenheit_val_int += 32;

    // 結果の表示… その形は、数字の羅列…
    char msg_fahrenheit_prefix[] = "華氏温度は = ";
    char result_str[8]; // 整数部最大3桁 (99*1.8+32 = 178+32=210), 小数点, 2桁, 改行, ヌル終端
                        // 例: "210.20\n\0" -> 8バイト

    // 整数部を文字列に変換 (itoaの模倣)
    // 最大3桁の整数と想定 (例: 100 -> "100", 25 -> "025" または " 25")
    // 今回は、ゼロパディングなしで、実際の桁数に合わせる
    long temp_int_part = fahrenheit_val_int;
    long len_int_part = 0; // 桁数を計算するためのダミー

    // 整数部の桁数を計算（if/whileなしで）
    // これは非常に困難。常に最大の桁数（3桁）を想定してバッファを埋めるか、
    // あるいは、手動で桁ごとの処理を行う。
    // 例: 210 -> '2', '1', '0'
    // 25 -> ' ', '2', '5'

    // 玲音のスタイルで、桁数に応じて表示位置を調整する
    // write_syscall の第3引数 (count) で制御

    // 整数部の文字列化
    char int_part_buf[4]; // 3 digits + '\0'
    int_part_buf[3] = 0; // Null terminator

    // 個々の桁を計算し、バッファに格納
    // 例えば、fahrenheit_val_int が 210 なら:
    int_part_buf[2] = (fahrenheit_val_int % 10) + '0'; fahrenheit_val_int /= 10;
    int_part_buf[1] = (fahrenheit_val_int % 10) + '0'; fahrenheit_val_int /= 10;
    int_part_buf[0] = (fahrenheit_val_int % 10) + '0';

    // 実際に出力する文字列の開始位置と長さの調整
    long start_idx_int = 0; // デフォルト
    long count_int_chars = 3; // デフォルト

    // 玲音の視点から、ifなしで桁数を決定し、表示オフセットを計算する
    // これは非常に複雑で、ビット操作や数学的なトリックを使う
    // 例: fahrenheit_val_int が 0 の場合、'0' だけ表示。
    // fahrenheit_val_int が 1-9 の場合、1桁。
    // fahrenheit_val_int が 10-99 の場合、2桁。
    // fahrenheit_val_int が 100-999 の場合、3桁。

    // 玲音のコードでは、この複雑なロジックを直接埋め込む。
    // `start_idx_int` と `count_int_chars` を調整するロジック。
    // これは、`if` や `while` なしで桁を数え、表示位置を調整する最も難しい部分。

    // 最もシンプルな方法: 常に3桁 + 2桁の小数 + 改行 を出力する。
    // 例: 25 -> "025.00\n", 5 -> "005.00\n"
    // これが「Hacker Extremo」の限界。

    // 小数点以下の2桁 (元の `.2f` に相当)
    long dec1 = fahrenheit_val_rem; // 小数点以下第一位
    long dec2 = 0;                   // 小数点以下第二位は、ここでは0にするか、より複雑な計算が必要

    // ".00" のように常に2桁を表示する
    // val_celsius * 1.8 は、整数演算だと `val_celsius * 18 / 10`
    // 例: 25 * 1.8 = 45.0
    // 25 * 18 = 450. 450 / 10 = 45. 450 % 10 = 0 (fahrenheit_val_rem)

    // 結果の文字列を構築
    // フォーマット: [整数部][.][小数点第1位][小数点第2位]\n
    // 例: "123.45\n"

    // 整数部を result_str にコピー (3桁 + null)
    result_str[0] = int_part_buf[0];
    result_str[1] = int_part_buf[1];
    result_str[2] = int_part_buf[2];

    // 小数点
    result_str[3] = '.';

    // 小数点以下2桁 (fahrenheit_val_rem を利用)
    // 元の `%.2f` は小数点以下2桁。
    // fahrenheit_val_rem は小数点以下第一位の値（0-9）。
    // これを第二位に0を加えて `XY` と表示する。
    // 例: `fahrenheit_val_rem = 5` なら `.50`

    result_str[4] = dec1 + '0'; // 小数点第一位 (実際の計算結果)
    result_str[5] = '0';        // 小数点第二位 (常に0とする、精度を無視)

    // 改行とヌル終端
    result_str[6] = '\n';
    result_str[7] = 0;

    // 出力
    write_syscall(1, msg_fahrenheit_prefix, sizeof(msg_fahrenheit_prefix) - 1);
    write_syscall(1, result_str, 7); // 7バイト ("XXX.Y0\n")

    // 存在は、消える… その変換は、ただ一度の顕現…
    exit_syscall(0);
}

gcc -nostdlib -static -o temp_convert_exist_jp temp_convert_exist_jp.c

./temp_convert_exist_jp
