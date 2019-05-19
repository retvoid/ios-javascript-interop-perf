#ifndef JSCoreTest_hpp
#define JSCoreTest_hpp

#include <stdio.h>

#include <iostream>
#include <JavaScriptCore/JavaScriptCore.h>

using namespace std;

JSValueRef ObjectCallAsFunctionCallback(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception) {
    //cout << "Hello World" << endl;
    return JSValueMakeUndefined(ctx);
}

int runJSCoreTest() {
    // Create JSCore VM
    JSContextGroupRef contextGroup = JSContextGroupCreate();
    // Create global context
    JSGlobalContextRef globalContext = JSGlobalContextCreateInGroup(contextGroup, nullptr);
    // Get global object in global context
    JSObjectRef globalObject = JSContextGetGlobalObject(globalContext);
    
    // Register native function
    JSStringRef logFunctionName = JSStringCreateWithUTF8CString("log");
    JSObjectRef functionObject = JSObjectMakeFunctionWithCallback(globalContext, logFunctionName, &ObjectCallAsFunctionCallback);
    
    JSObjectSetProperty(globalContext, globalObject, logFunctionName, functionObject, kJSPropertyAttributeNone, nullptr);
    
    unsigned run_count = 0;

    for (int i = 0; i < 30; i++) {
        run_count += 3000;
        std::string str = "for (var i = 0; i < " + std::to_string(run_count) + "; i++) log(i)";
        JSStringRef logCallStatement = JSStringCreateWithUTF8CString(str.c_str());
        
        // Perf
        NSDate *methodStart = [NSDate date];
        
        JSEvaluateScript(globalContext, logCallStatement, nullptr, nullptr, 1,nullptr);
        
        NSDate *methodFinish = [NSDate date];
        NSTimeInterval executionTime = [methodFinish timeIntervalSinceDate:methodStart];
        NSLog(@"run %u times executionTime = %fms", run_count, executionTime * 1000 / run_count);
        
        JSStringRelease(logCallStatement);
    }
    
    
    /* memory management code to prevent memory leaks */
    
    JSGlobalContextRelease(globalContext);
    JSContextGroupRelease(contextGroup);
    JSStringRelease(logFunctionName);
    
    return 0;
}

#endif /* JSCoreTest_hpp */
