#import "NetworkManager.h"

@implementation NetworkManager

+ (instancetype)sharedManager {
    static NetworkManager *sharedManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedManager = [[self alloc] init];
    });
    return sharedManager;
}

- (void)sendMessage:(NSString *)message completion:(CompletionHandler)completion {
    NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
    NSString *apiKey = [defaults stringForKey:@"apiKey"];
    NSString *baseUrl = [defaults stringForKey:@"baseUrl"];
    NSString *botIdentity = [defaults stringForKey:@"botIdentity"];
    NSString *model = [defaults stringForKey:@"model"] ?: @"gpt-4";
    
    if (!apiKey || !baseUrl) {
        NSError *error = [NSError errorWithDomain:@"NetworkManager"
                                           code:1
                                       userInfo:@{NSLocalizedDescriptionKey: @"请先在设置中配置 API Key 和 Base URL"}];
        completion(nil, error);
        return;
    }
    
    NSURL *url = [NSURL URLWithString:baseUrl];
    NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:url];
    request.HTTPMethod = @"POST";
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-Type"];
    [request setValue:[NSString stringWithFormat:@"Bearer %@", apiKey] forHTTPHeaderField:@"Authorization"];
    
    NSDictionary *bodyDict = @{
        @"model": model,
        @"messages": @[
            @{
                @"role": @"system",
                @"content": botIdentity ?: @"你是一个有帮助的AI助手。"
            },
            @{
                @"role": @"user",
                @"content": message
            }
        ]
    };
    
    NSError *error;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:bodyDict options:0 error:&error];
    if (error) {
        completion(nil, error);
        return;
    }
    
    request.HTTPBody = jsonData;
    
    NSURLSession *session = [NSURLSession sharedSession];
    NSURLSessionDataTask *task = [session dataTaskWithRequest:request
                                          completionHandler:^(NSData * _Nullable data,
                                                            NSURLResponse * _Nullable response,
                                                            NSError * _Nullable error) {
        if (error) {
            dispatch_async(dispatch_get_main_queue(), ^{
                completion(nil, error);
            });
            return;
        }
        
        NSError *jsonError;
        NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:data
                                                                   options:0
                                                                     error:&jsonError];
        if (jsonError) {
            dispatch_async(dispatch_get_main_queue(), ^{
                completion(nil, jsonError);
            });
            return;
        }
        
        NSString *aiResponse = jsonResponse[@"choices"][0][@"message"][@"content"];
        dispatch_async(dispatch_get_main_queue(), ^{
            completion(aiResponse, nil);
        });
    }];
    
    [task resume];
}

@end 