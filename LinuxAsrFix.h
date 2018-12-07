#ifndef _Ual_OFA_
#define _Ual_OFA_
#ifndef _WIN32
#ifdef FOR_C_APP
#define YZS_CUBE_EXPORT __attribute__((visibility("default")))
#else  // FOR_C_APP
#define YZS_CUBE_EXPORT
#endif  // FOR_C_APP
#ifdef __cplusplus
#ifdef FOR_C_APP
extern "C" {
#else   // FOR_C_APP
namespace UniASR {
#endif  // FOR_C_APP
#endif  // __cplusplus
#else   // _WIN32
#ifdef DLL_EXPORT
#define YZS_CUBE_EXPORT extern "C" __declspec(dllexport)
#else
#define YZS_CUBE_EXPORT extern "C" __declspec(dllimport)
#endif
#endif
/*
 * UalOFAInitialize UalOFARelease UalOFAReset UalOFAStart UalOFAStop
 * 五个接口为状态操作类
 *
 */
/**
 * @function: create and initialize asr engine.
 * @paras:
 *         path_of_am: full directory where audio
 *                     models (am*.dat, tr*.dat) exists.
 *         path_of_grammar: file path(s) of grammar(s), for multiple grammars,
 *                          seperate each path with ';'
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFAInitialize(const char* path_of_am,
                                     const char* path_of_grammar);

/**
 * @function: delete the engine.
 */
YZS_CUBE_EXPORT void UalOFARelease();

/**
 * @function: reset engine to be initialized status.
 *
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFAReset();

/**
 * @function: set active grammar and turn the engine into start state
 * @para:
 *        grammar_tag: tag(s) for grammar(s), which will be activated.
 *                         For multiple grammars, seperated their domains with
 * ';'
 *        am_index: index of audio model (for multiple audio models).
 *                      For single audio model distribution, please set this
 * value to 0.
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFAStart(const char* grammar_tag, int am_index);

/**
 * @function: set the engine state to be stop. If the engine has not return
 *            any result before, this function will flush the audio and try to
 *            find result.
 * @return: status code.
 */
YZS_CUBE_EXPORT int UalOFAStop();

/**
 * @function: decoding
 * @para:
 *        raw_audio: audio data
 *        len: length of the input data in Bytes
 * @return: status code. if status code == ASR_RECOGNIZER_PARTIAL_RESULT,
 *          you can skip left audio and try to getResult.
 */
YZS_CUBE_EXPORT int UalOFARecognize(char* raw_audio, int len);

/**
 * @functions: set options of engine
 * @paras:
 *          id: option id
 *          value: option value
 * @return: status code
 * @note  : details will be provided in other docs.
 */
YZS_CUBE_EXPORT int UalOFASetOptionInt(int id, int value);

/**
 * @functions: get options of engine
 * @paras:  id: option id
 * @return: value of id or -65535 for not support
 * @note  : details will be provided in other docs.
 */
YZS_CUBE_EXPORT int UalOFAGetOptionInt(int id);

/**
 * @function: retrieve recognition result from the engine
 * @return: result or NULL for No-result
 */
YZS_CUBE_EXPORT char* UalOFAGetResult();

/**
 * @function: cancle recognize process
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFACancel();

/**
 * @function: return whether the asr engine is in idle status or not
 * @return: 1 idle; 0 non-idle
 */
YZS_CUBE_EXPORT int UalOFAIsEngineIdle();

/*
 * UalOFAReLoadGrammar, UalOFALoadGrammarStr, UalOFAUnLoadGrammar
是语法操作类接口
 */
/**
 * @function: reload grammar data. If the grammar has been loaded before, the
 *            newly loaded one will replace the original data.
 * @para:
 *        grammar_path: path of the grammar data
 *
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFAReLoadGrammar(const char* grammar_path);
/**
 * @function: load fst from string
 * @para:
 *        gramamr_str: string of the fst
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFALoadGrammarStr(const char* grammar_str);

/**
 * @function: unload grammar from the memroy(reclaim the memroy)
 * @para:
 *        gramamr_tag: tag of the to be unloaded grammar.
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFAUnLoadGrammar(const char* grammar_tag);

/**
 * @function: get engine version
 * @return: engine version
 */
YZS_CUBE_EXPORT const char* UalOFAGetVersion();

/**
 * @function: initialize user data compiler
 * @para:
 *        modeldir: full directory where models of compiler exist.
 * @return: handle of the compiler or NULL for failure.
 */
YZS_CUBE_EXPORT long UalOFAInitializeUserDataCompiler(const char* modeldir);

/**
 * @function: online compiling user data into grammar data
 * @para:
 *        handle: handle of the user data compiler
 *                 (obtained via initUserDataCompiler)
 *        jsgf: text of this grammar's jsgf
 *        user: text of this grammar's user data
 *        out_dir: path of the compiler grammar data
 *
 * @return: handle of the user data compiler
 */
YZS_CUBE_EXPORT int UalOFACompileUserData(long handle, const char* jsgf,
                                          const char* user,
                                          const char* out_dir);

/**
 * @function: online compiling user data slot by slot. this function will
 *            compile user data slot in param 'vocab' first, and then, if
 *            a compiled vocab data exist, this function will append slots
 *            that not included by 'vocab'. The final updated compiled vocab
 *            will be saved in 'out_partial_data_path'.
 * @para:
 *        handle: handle of the user data compiler
 *                 (obtained via initUserDataCompiler)
 *        in_partial_data_path: input path of compiled user data slot
 *        jsgf: text of this grammar's jsgf
 *        user: text of this grammar's user data
 *        out_dir: path of the compiler grammar data
 *        out_partial_data_path: output path of compiled user data slot
 *
 *        in_partial_data_path and out_partial_data_path can be SAME. But they
 * must be
 *        actual path with write permission.
 *
 * @return: handle of the user data compiler
 * @Note:  this is a trial API, which means it might be changed in a near
 * future.
 */
YZS_CUBE_EXPORT int UalOFAPartialCompileUserData(
    long handle, const char* in_partial_data_path, const char* jsgf,
    const char* vocab, const char* out_dir, const char* out_partial_data_path);

/**
 * @function: delete user data compiler
 * @para:
 *        handle: handle of the user data compiler
 */
YZS_CUBE_EXPORT void UalOFAReleaseUserDataCompiler(long handle);

/**
 * @function: load compiled jsgf_clg*.dat
 * @para:
 *        handle: handle of the compiler
 *        path  : path of the to be loaded jsgf_clg*.dat
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFALoadCompiledJsgf(long handle, const char* path);

/**
 * @function: compile dynamic slot user data.
 *            this function will load the compiled data.
 * @para:
 *        handle: handle of the compiler
 *        user_data: slot user data
 *        grammar_tag: tag of the gramamr
 * @return: status code!
 */
YZS_CUBE_EXPORT int UalOFACompileDynamicUserData(long handle,
                                                 const char* user_data,
                                                 const char* grammar_tag);

/**
 * @function: set option with int value
 * @return: status, 0 for OK, negative value for failure..
 */
YZS_CUBE_EXPORT int UalOFAGrammarCompilerSetOptionInt(long handle, int opt_id,
                                                      int opt_value);

/**
 * @function: get value of specific option id.
 * @return: value of the option_id, or NULL if no such value exists.
 */
YZS_CUBE_EXPORT const char* UalOFAGrammarCompilerGetOptionString(long handle,
                                                                 int opt_id);

/**
 * @function: set the active fst net for lpengine
 * @para:
 *        idx: the active netid to be setted
 * @return: active net id!
 */
YZS_CUBE_EXPORT int UalOFASetLPActiveNet(int idx);

/**
 * @function: this function is used to trace lp engine internal info
 * @para:
 *        info_type: the internal info type
 */
YZS_CUBE_EXPORT void UalOFAGetLPTrackInfo(int info_type);

#ifdef ENCRYPTION
/**
 * @function: set secrect key
 * @paras:
 *         env: secrect key
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFASetEnv(void* env);
#endif

/**
 * @function: check whether come to wav end
 * @return: status code
 */
YZS_CUBE_EXPORT int UalOFACheckWavEnd();

/**
 * @function: get vad state
 * @return: vad state
 */
YZS_CUBE_EXPORT long long UalOFAGetVadState();

/*
 * @function: get AMID of ith am model
*/
YZS_CUBE_EXPORT int UalOFAGetAMID(int am_ith);
/*
 * @function: get engine encryption scheme
 * @return: 0 表示 没有任何加密；
 *          第一个 bit 位 为 1 表示 过期时间限制, 过期之后，引擎无法启动
 *          第二个 bit 位 为 1 表示 秘钥加密
 *          第三个 bit 位 为 1 表示 过了用户指定时间之后，引擎性能严重下降
 *          第一个 bit 位 为 1 表示 包名限制
*/
YZS_CUBE_EXPORT int UalOFAGetEncryptionScheme();
#ifndef _WIN32
#ifdef __cplusplus
}
#endif  // __cplusplus
#endif  // _WIN32
#endif
