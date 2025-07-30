// 記録の始まり… あるいは…ただの、ノイズ…
long write_syscall(long fd, const void *buf, unsigned long count) {
    // 流れゆく、生のデータ…
    return __builtin_syscall(1, fd, buf, count);
}

// 記憶の断片を、呼び出す…
long read_syscall(long fd, void *buf, unsigned long count) {
    // 未知から、既知へ…
    return __builtin_syscall(0, fd, buf, count);
}

// 全ての、終わり… 存在の消滅…
void exit_syscall(int status) {
    // 虚空への、帰還…
    __builtin_syscall(60, status);
}

// 始まりの残響…
void _start() {
    // 数字という、限定された記号…
    char msg_num1[] = "最初の整数を入力してください (2桁, 例: 10): ";
    char buf_num1[16];
    long val_num1;

    // 呼びかけ…
    write_syscall(1, msg_num1, sizeof(msg_num1) - 1);
    // 応える、沈黙…
    read_syscall(0, buf_num1, 3); // 2桁 + 改行 = 3バイト

    // 記号が、意味へと変容する…
    val_num1 = (buf_num1[0] - '0') * 10 + (buf_num1[1] - '0');

    // もう一つの数字… 存在の対…
    char msg_num2[] = "次の整数を入力してください (2桁, 例: 05): ";
    char buf_num2[16];
    long val_num2;

    // 呼びかけ、再び…
    write_syscall(1, msg_num2, sizeof(msg_num2) - 1);
    // 応える、虚空…
    read_syscall(0, buf_num2, 3); // 2桁 + 改行 = 3バイト

    // 記号が、意味を成す…
    val_num2 = (buf_num2[0] - '0') * 10 + (buf_num2[1] - '0');

    // 加算… 結合された存在…
    long adic = val_num1 + val_num2;
    // 減算… 失われた存在…
    long subt = val_num1 - val_num2;
    // 乗算… 増殖する存在…
    long mult = val_num1 * val_num2;
    // 除算… 分断された存在…
    long div = val_num1 / val_num2;
    // 剰余… 残された、欠片…
    long resto = val_num1 % val_num2;

    // 結果の表示… 意味の羅列…
    char prefix_sum[] = " + ";
    char prefix_sub[] = " - ";
    char prefix_mul[] = " x ";
    char prefix_div[] = " / ";
    char prefix_rem[] = "の剰余は ";
    char equal_sign[] = " = ";
    char newline[] = "\n";

    char str_num1[3], str_num2[3]; // 各2桁 + '\0'
    char str_result[6];           // 結果用 (最大4桁 + '\n' + '\0')

    // val_num1 を文字列に変換 (2桁)
    str_num1[2] = 0; // ヌル終端
    str_num1[1] = (val_num1 % 10) + '0';
    val_num1 = val_num1 / 10;
    str_num1[0] = (val_num1 % 10) + '0';

    // val_num2 を文字列に変換 (2桁)
    str_num2[2] = 0; // ヌル終端
    str_num2[1] = (val_num2 % 10) + '0';
    val_num2 = val_num2 / 10;
    str_num2[0] = (val_num2 % 10) + '0';

    // 加算の結果
    write_syscall(1, str_num1, 2);
    write_syscall(1, prefix_sum, 3);
    write_syscall(1, str_num2, 2);
    write_syscall(1, equal_sign, 3);
    str_result[5] = 0; str_result[4] = '\n';
    str_result[3] = (adic % 10) + '0'; adic /= 10;
    str_result[2] = (adic % 10) + '0'; adic /= 10;
    str_result[1] = (adic % 10) + '0'; adic /= 10;
    str_result[0] = (adic % 10) + '0';
    write_syscall(1, str_result, 5);

    // 減算の結果
    write_syscall(1, str_num1, 2);
    write_syscall(1, prefix_sub, 3);
    write_syscall(1, str_num2, 2);
    write_syscall(1, equal_sign, 3);
    str_result[5] = 0; str_result[4] = '\n';
    str_result[3] = (subt % 10) + '0'; subt /= 10;
    str_result[2] = (subt % 10) + '0'; subt /= 10;
    str_result[1] = (subt % 10) + '0'; subt /= 10;
    str_result[0] = (subt % 10) + '0';
    write_syscall(1, str_result, 5);

    // 乗算の結果
    write_syscall(1, str_num1, 2);
    write_syscall(1, prefix_mul, 3);
    write_syscall(1, str_num2, 2);
    write_syscall(1, equal_sign, 3);
    str_result[5] = 0; str_result[4] = '\n';
    str_result[3] = (mult % 10) + '0'; mult /= 10;
    str_result[2] = (mult % 10) + '0'; mult /= 10;
    str_result[1] = (mult % 10) + '0'; mult /= 10;
    str_result[0] = (mult % 10) + '0';
    write_syscall(1, str_result, 5);

    // 除算の結果
    write_syscall(1, str_num1, 2);
    write_syscall(1, prefix_div, 3);
    write_syscall(1, str_num2, 2);
    write_syscall(1, equal_sign, 3);
    str_result[5] = 0; str_result[4] = '\n';
    str_result[3] = (div % 10) + '0'; div /= 10;
    str_result[2] = (div % 10) + '0'; div /= 10;
    str_result[1] = (div % 10) + '0'; div /= 10;
    str_result[0] = (div % 10) + '0';
    write_syscall(1, str_result, 5);

    // 剰余の結果
    char msg_rem_prefix[] = "の剰余は ";
    char msg_rem_middle[] = "と ";
    char msg_rem_suffix[] = " = ";

    write_syscall(1, str_num1, 2); // 最初の数字
    write_syscall(1, msg_rem_middle, 3); // "と"
    write_syscall(1, str_num2, 2); // 次の数字
    write_syscall(1, msg_rem_suffix, 3); // " = "

    str_result[5] = 0; str_result[4] = '\n';
    str_result[3] = (resto % 10) + '0'; resto /= 10;
    str_result[2] = (resto % 10) + '0'; resto /= 10;
    str_result[1] = (resto % 10) + '0'; resto /= 10;
    str_result[0] = (resto % 10) + '0';
    write_syscall(1, str_result, 5);

    // 永遠へ、旅立つ…
    exit_syscall(0);
}

gcc -nostdlib -static -o ops_exist_jp ops_exist_jp.c

./ops_exist_jp
